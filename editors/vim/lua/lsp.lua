local client = nil

local function start()
  if client == nil then
    local script_dir = debug.getinfo(1, "S").source:match('@?(.*/)')
    local plugin_dir = vim.fn.resolve(script_dir .. '../')
    local ls_path = vim.fn.resolve(plugin_dir .. '/../vscode/out/server/src/server.js')
    local file_readable = vim.fn.filereadable(ls_path) ~= 0

    if file_readable then
      client = vim.lsp.start_client {
        cmd = { 'node', ls_path, '--stdio' }
      }
    else
      vim.notify_once("\nCouldn't find Jakt language server.\nPlease make sure you follow the documentation at https://github.com/SerenityOS/jakt/blob/main/editors/vim/README.md",  
      vim.log.levels.WARN)
      return
    end
  end
  
  vim.lsp.buf_attach_client(0, client)
end


return {
  start = start
}


