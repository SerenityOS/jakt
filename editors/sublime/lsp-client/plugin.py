import os
from lsp_utils import NpmClientHandler

def plugin_loaded():
    LspYaktPlugin.setup()

def plugin_unloaded():
    LspYaktPlugin.cleanup()

class LspYaktPlugin(NpmClientHandler):
    package_name = __package__
    server_directory = 'server'
    server_binary_path = os.path.join(
        server_directory, 'src/server.js'
    )
