au BufRead,BufNewFile *.jakt set filetype=jakt
if has("nvim")
  let s:started = 0
  function! s:Start()
    if s:started
      return
    end
    let s:started = 1
    lua require('lsp').start()
  endfunction
  au FileType jakt call s:Start()
end
