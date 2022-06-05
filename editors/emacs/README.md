# Jakt Mode
`jakt-mode` is a emacs major mode that provides syntax highlighting and indentation.  
## Installation
Clone this repository and add this to your `init.el`. 
```
(add-to-list 'load-path "/path/to/jakt-mode/")
(autoload 'jakt-mode "jakt-mode" nil t)
(add-to-list 'auto-mode-alist '("\\.jakt\\'" . jakt-mode))
```
