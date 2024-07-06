(defvar jakt-mode-syntax-table nil "Syntax table for `jakt-mode`.")

(setq jakt-mode-syntax-table
      (let ((syntax-table (make-syntax-table)))
        (modify-syntax-entry ?\/ ". 12b" syntax-table)
        (modify-syntax-entry ?\n "> b" syntax-table)
        (modify-syntax-entry ?_ "w" syntax-table)
        syntax-table))

(defcustom jakt-indent-offset 4
  "Indent Jakt code by this number of spaces."
  :type 'integer
  :group 'jakt-mode
  :safe #'integerp)

(defun jakt-indent-line ()
  "Indent a jakt line."
  (let (indent
        boi-p                         
        move-eol-p
        (point (point)))             
    (save-excursion
      (back-to-indentation)
      (setq indent (car (syntax-ppss))
            boi-p (= point (point)))
      (when (and (eq (char-after) ?\n)
                 (not boi-p))
        (setq indent 0))
      (when boi-p
        (setq move-eol-p t))
      (when (or (eq (char-after) ?\))
                (eq (char-after) ?\}))
        (setq indent (1- indent)))
      (delete-region (line-beginning-position)
                     (point))
      (indent-to (* jakt-indent-offset indent)))
    (when move-eol-p
      (move-end-of-line nil))))

(setq jakt-font-lock-defaults
      (let* (
             (jakt-conditional '("if" "else" "match" "guard"))
             (jakt-repeat '("while" "for" "loop"))
             (jakt-execution '("return" "break" "continue" "throw" "yield"))
             (jakt-boolean '("true" "false"))
             (jakt-keyword '("fn" "extern" "comptime" "import" "export"))
             (jakt-exception '("throws"))
             (jakt-macro '("defer" "unsafe" "throw" "try" "must" "catch" "cpp"))
             (jakt-var-decls '("mut" "let" "anon" "raw"))
             (jakt-types '("i8" "i16" "i32" "i16" "i32" "i64" "u8" "u16" "u32"
                           "u64" "f32" "f64" "bool" "c_int" "c_char" "usize"
                           "String" "void"))
             (jakt-builtin-fn '("print" "println")) 
             (jakt-operators '("not" "and" "or" "as" "in")) 
             (jakt-structure '("struct" "class" "enum" "namespace")) 
             (jakt-constant '("this"))
             (jakt-visibility '("public" "private")) 

             (conditional-regex (regexp-opt jakt-conditional 'words))
             (repeat-regex (regexp-opt jakt-repeat 'words))
             (execution-regex (regexp-opt jakt-execution 'words))
             (boolean-regex (regexp-opt jakt-boolean 'words))
             (keyword-regex (regexp-opt jakt-keyword 'words))
             (exception-regex (regexp-opt jakt-exception 'words))
             (macro-regex (regexp-opt jakt-macro 'words))
             (var-decls-regex (regexp-opt jakt-var-decls 'words))
             (types-regex (regexp-opt jakt-types 'words))
             (builtin-fn-regex (regexp-opt jakt-builtin-fn 'words))
             (operators-regex (regexp-opt jakt-operators 'words))
             (structure-regex (regexp-opt jakt-structure 'words))
             (constant-regex (regexp-opt jakt-constant 'words))
             (visibility-regex (regexp-opt jakt-visibility 'words)))

        `(
          ("[[:upper:]]\\w*" . 'font-lock-type-face)
          (,exception-regex . 'font-lock-warning-face) 
          (,operators-regex . 'font-lock-keyword-face)
          (,conditional-regex . 'font-lock-keyword-face) 
          (,repeat-regex . 'font-lock-keyword-face) 
          (,boolean-regex . 'font-lock-keyword-face) 
          (,types-regex . 'font-lock-type-face)
          (,constant-regex . 'font-lock-constant-face)
          (,builtin-fn-regex . 'font-lock-builtin-face)
          (,keyword-regex . 'font-lock-keyword-face)
          (,var-decls-regex . 'font-lock-variable-name-face)
          (,macro-regex . 'font-lock-preprocessor-face) 
          (,execution-regex . 'font-lock-keyword-face) 
          (,structure-regex . 'font-lock-keyword-face)
          (,visibility-regex . 'font-lock-keyword-face)
          )))

;;;###autoload
(define-derived-mode jakt-mode prog-mode "Jakt"
  "Major mode for Jakt code." 
  :group 'jakt-mode
  :syntax-table jakt-mode-syntax-table
  (setq font-lock-defaults '((jakt-font-lock-defaults)))
  (set-syntax-table jakt-mode-syntax-table)
  (setq-local comment-start "//")
  (setq-local comment-end "")
  (setq-local indent-line-function #'jakt-indent-line))

(provide 'jakt-mode)
