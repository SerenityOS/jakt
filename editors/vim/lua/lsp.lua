-- Set per Neovim *instance*, so that opening another Jakt file (buffer)
-- in the same instance reuses the already spawned client.
local client = nil

local function start()
  if client == nil then
    -- Resolve paths so we don't depend on neovim's CWD:
    -- `script_dir` will always point to
    --  <symlink by plugin manager>/lua
    local script_dir = debug.getinfo(1, "S").source:match('@?(.*/)')
    -- We use `resolve` so that `plugin_dir` points to
    -- <path/to/jakt>/editors/vim (since `resolve` resolves symlinks)
    local plugin_dir = vim.fn.resolve(script_dir .. '../')
    -- From there we can point correctly to the LSP server.
    local ls_path = vim.fn.resolve(plugin_dir .. '/../vscode/out/server/src/server.js')

    -- We need the file to be readable by node, otherwise we'll warn the user
    -- and keep going without the client.
    local is_file_readable = vim.fn.filereadable(ls_path) ~= 0
    if is_file_readable then
      client = vim.lsp.start_client {
        cmd = { 'node', ls_path, '--stdio' }
      }
    else
      -- We use a starting `\n` because currently Neovim displays
      -- this warning with some indent. This newline serves a workaround.
      -- FIXME: Remove newline workaround once Neovim properly displays warnings
      vim.notify_once("\nCouldn't find Jakt language server.\nPlease make sure you follow the documentation at https://github.com/SerenityOS/jakt/blob/main/editors/vim/README.md",  
      vim.log.levels.WARN)
      return
    end
  end
  -- Attach our LSP client handle to the current buffer. 
  -- See :help lsp and search for `buf_attach_client` for more info.
  vim.lsp.buf_attach_client(0, client)
end


return {
  start = start
}


