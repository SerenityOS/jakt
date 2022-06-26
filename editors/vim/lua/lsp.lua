local client = nil

local function start()
  if client == nil then
    local script_dir = debug.getinfo(1, "S").source:match('@?(.*/)')
    local plugin_dir = vim.fn.resolve(script_dir .. '../')
    local ls_path = vim.fn.resolve(plugin_dir .. '/../vscode/out/server/src/server.js')
    client = vim.lsp.start_client {
      cmd = { 'node', ls_path, '--stdio' }
    }
  end
  
  vim.lsp.buf_attach_client(0, client)
end


return {
  start = start
}


