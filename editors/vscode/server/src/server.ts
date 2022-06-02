/* --------------------------------------------------------------------------------------------
 * Copyright (c) Microsoft Corporation. All rights reserved.
 * Licensed under the MIT License. See License.txt in the project root for license information.
 * ------------------------------------------------------------------------------------------ */
import {
	createConnection,
	TextDocuments,
	Diagnostic,
	DiagnosticSeverity,
	ProposedFeatures,
	InitializeParams,
	DidChangeConfigurationNotification,
	CompletionItem,
	CompletionItemKind,
	TextDocumentPositionParams,
	TextDocumentSyncKind,
	InitializeResult,
	Location
} from 'vscode-languageserver/node';

import {
	Position,
	TextDocument
} from 'vscode-languageserver-textdocument';

// Create a connection for the server, using Node's IPC as a transport.
// Also include all preview / proposed LSP features.
const connection = createConnection(ProposedFeatures.all);

// Create a simple text document manager.
const documents: TextDocuments<TextDocument> = new TextDocuments(TextDocument);

let hasConfigurationCapability = false;
let hasWorkspaceFolderCapability = false;
let hasDiagnosticRelatedInformationCapability = false;

import fs = require('fs');
import tmp = require('tmp');

import util = require('node:util');
import { TextEncoder } from 'node:util';
// eslint-disable-next-line @typescript-eslint/no-var-requires
const exec = util.promisify(require('node:child_process').exec);

const tmpFile = tmp.fileSync();

connection.onInitialize((params: InitializeParams) => {
	const capabilities = params.capabilities;

	// Does the client support the `workspace/configuration` request?
	// If not, we fall back using global settings.
	hasConfigurationCapability = !!(
		capabilities.workspace && !!capabilities.workspace.configuration
	);
	hasWorkspaceFolderCapability = !!(
		capabilities.workspace && !!capabilities.workspace.workspaceFolders
	);
	hasDiagnosticRelatedInformationCapability = !!(
		capabilities.textDocument &&
		capabilities.textDocument.publishDiagnostics &&
		capabilities.textDocument.publishDiagnostics.relatedInformation
	);

	const result: InitializeResult = {
		capabilities: {
			textDocumentSync: TextDocumentSyncKind.Incremental,
			// Tell the client that this server doesn't support code completion. (yet)
			completionProvider: {
				resolveProvider: false,
				triggerCharacters: ['.']
			},
			definitionProvider: true,
			hoverProvider: true,
		}
	};
	if (hasWorkspaceFolderCapability) {
		result.capabilities.workspace = {
			workspaceFolders: {
				supported: true
			}
		};
	}
	return result;
});

connection.onInitialized(() => {
	if (hasConfigurationCapability) {
		// Register for all configuration changes.
		connection.client.register(DidChangeConfigurationNotification.type, undefined);
	}
	if (hasWorkspaceFolderCapability) {
		connection.workspace.onDidChangeWorkspaceFolders(_event => {
			connection.console.log('Workspace folder change event received.');
		});
	}
});

connection.onDefinition(async (request) => {
	const document = documents.get(request.textDocument.uri);

	let text = document?.getText();

	if (typeof text == "string") {
		console.log("request: ");
		console.log(request);
		console.log("index: " + convertPosition(request.position, text));
		let stdout = await runCompiler(text, "-g " + convertPosition(request.position, text));
		console.log("got: ", stdout);

		const lines = stdout.split('\n').filter(l => l.length > 0);
		for (const line of lines) {

			const obj = JSON.parse(line);
			console.log("going to definition");
			console.log(obj);

			return { uri: request.textDocument.uri, range: { start: convertSpan(obj.start, text), end: convertSpan(obj.end, text) } };
		}
	}
});

connection.onHover(async (request) => {
	const document = documents.get(request.textDocument.uri);

	let text = document?.getText();

	if (typeof text == "string") {
		console.log("request: ");
		console.log(request);
		console.log("index: " + convertPosition(request.position, text));
		let stdout = await runCompiler(text, "-v " + convertPosition(request.position, text));
		console.log("got: ", stdout);

		const lines = stdout.split('\n').filter(l => l.length > 0);
		for (const line of lines) {

			const obj = JSON.parse(line);
			console.log("hovering");
			console.log(obj);

			if (obj.hover != "") {
				return { contents: obj.hover };
			}
		}
	}

	return null;
});

// The example settings
interface ExampleSettings {
	maxNumberOfProblems: number;
}

// The global settings, used when the `workspace/configuration` request is not supported by the client.
// Please note that this is not the case when using this server with the client provided in this example
// but could happen with other clients.
const defaultSettings: ExampleSettings = { maxNumberOfProblems: 1000 };
let globalSettings: ExampleSettings = defaultSettings;

// Cache the settings of all open documents
const documentSettings: Map<string, Thenable<ExampleSettings>> = new Map();

connection.onDidChangeConfiguration(change => {
	if (hasConfigurationCapability) {
		// Reset all cached document settings
		documentSettings.clear();
	} else {
		globalSettings = <ExampleSettings>(
			(change.settings.languageServerExample || defaultSettings)
		);
	}

	// Revalidate all open text documents
	documents.all().forEach(validateTextDocument);
});

function getDocumentSettings(resource: string): Thenable<ExampleSettings> {
	if (!hasConfigurationCapability) {
		return Promise.resolve(globalSettings);
	}
	let result = documentSettings.get(resource);
	if (!result) {
		result = connection.workspace.getConfiguration({
			scopeUri: resource,
			section: 'jaktLanguageServer'
		});
		documentSettings.set(resource, result);
	}
	return result;
}

// Only keep settings for open documents
documents.onDidClose(e => {
	documentSettings.delete(e.document.uri);
});

// The content of a text document has changed. This event is emitted
// when the text document first opened or when its content has changed.
documents.onDidChangeContent(change => {
	validateTextDocument(change.document);
});


function convertSpan(index: number, text: string): Position {
	let buffer = new TextEncoder().encode(text);
	let line = 0;
	let character = 0;

	let i = 0;
	while (i < text.length) {
		if (i == index) {
			return { line, character };
		}

		if (buffer.at(i) == 0x0A) {
			line++;
			character = 0;
		} else {
			character++;
		}

		i++;
	}

	return { line, character };
}

function convertPosition(position: Position, text: string): number {
	let line = 0;
	let character = 0;
	let buffer = new TextEncoder().encode(text);

	let i = 0;
	while (i < text.length) {
		if (line == position.line && character == position.character) {
			return i;
		}

		if (buffer.at(i) == 0x0A) {
			line++;
			character = 0;
		} else {
			character++;
		}

		i++;
	}

	return i
}

async function runCompiler(text: string, flags: string): Promise<string> {
	try {
		fs.writeFileSync(tmpFile.name, text);
	} catch (error) {
		console.log(error);
	}

	let stdout: string;
	try {
		const output = await exec("jakt " + flags + " " + tmpFile.name);
		console.log(output);
		stdout = output.stdout;
	} catch (e: any) {
		stdout = e.stdout;
		if (e.signal != null) {
			console.log("compile failed: ");
			console.log(e);
		}
	}

	return stdout
}

async function validateTextDocument(textDocument: TextDocument): Promise<void> {
	if (!hasDiagnosticRelatedInformationCapability) {
		console.error('Trying to validate a document with no diagnostic capability');
		return;
	}

	// // In this simple example we get the settings for every validate run.
	// const settings = await getDocumentSettings(textDocument.uri);

	// The validator creates diagnostics for all uppercase words length 2 and more
	const text = textDocument.getText();

	let stdout = await runCompiler(text, "-c -j");

	const diagnostics: Diagnostic[] = [];

	const lines = stdout.split('\n').filter(l => l.length > 0);
	for (const line of lines) {
		console.log(line);
		try {
			const obj = JSON.parse(line);

			let severity: DiagnosticSeverity = DiagnosticSeverity.Error;

			switch (obj.severity) {
				case "Information": severity = DiagnosticSeverity.Information; break;
				case "Hint": severity = DiagnosticSeverity.Hint; break;
				case "Warning": severity = DiagnosticSeverity.Warning; break;
				case "Error": severity = DiagnosticSeverity.Error; break;
			}

			const position_start = convertSpan(obj.span.start, text);
			const position_end = convertSpan(obj.span.end, text);

			const diagnostic: Diagnostic = {
				severity,
				range: {
					start: position_start,
					end: position_end
				},
				message: obj.message,
				source: textDocument.uri
			};

			console.log(diagnostic);

			diagnostics.push(diagnostic);
		} catch (e) {
			console.error(e);
		}

	}

	// Send the computed diagnostics to VSCode.
	connection.sendDiagnostics({ uri: textDocument.uri, diagnostics });
}

connection.onDidChangeWatchedFiles(_change => {
	// Monitored files have change in VSCode
	connection.console.log('We received an file change event');
});

// This handler provides the initial list of the completion items.
connection.onCompletion(
	async (request: TextDocumentPositionParams): Promise<CompletionItem[]> => {
		// The pass parameter contains the position of the text document in
		// which code complete got requested. For the example we ignore this
		// info and always provide the same completion items.

		const document = documents.get(request.textDocument.uri);

		let text = document?.getText();

		if (typeof text == "string") {
			console.log("completion request: ");
			console.log(request);
			let index = convertPosition(request.position, text) - 1;
			console.log("index: " + index);
			let stdout = await runCompiler(text, "-m " + index);
			console.log("got: ", stdout);

			const lines = stdout.split('\n').filter(l => l.length > 0);
			for (const line of lines) {

				const obj = JSON.parse(line);
				console.log("completions");
				console.log(obj);

				let output = []
				let index = 1
				for (const completion of obj.completions) {
					output.push({
						label: completion,
						kind: CompletionItemKind.Field,
						data: index
					});
					index++;
				}
				return output;
			}
		}

		return [];
	}
);

// This handler resolves additional information for the item selected in
// the completion list.
connection.onCompletionResolve(
	(item: CompletionItem): CompletionItem => {
		if (item.data === 1) {
			item.detail = 'TypeScript details';
			item.documentation = 'TypeScript documentation';
		} else if (item.data === 2) {
			item.detail = 'JavaScript details';
			item.documentation = 'JavaScript documentation';
		}
		return item;
	}
);

// Make the text document manager listen on the connection
// for open, change and close text document events
documents.listen(connection);

// Listen on the connection
connection.listen();
