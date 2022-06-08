" Vim syntax file
" Language: Jakt
" Latest Revision: 2022-05-25

if exists("b:current_syntax")
  finish
endif

let s:cpo_save = &cpo
set cpo&vim

let s:jakt_syntax_keywords = {
    \   'jaktConditional' :["if"
    \ ,                     "else"
    \ ,                     "match"
    \ ,                    ]
    \ , 'jaktRepeat' :["while"
    \ ,                "for"
    \ ,                "loop"
    \ ,               ]
    \ , 'jaktExecution' :["return"
    \ ,                   "break"
    \ ,                   "continue"
    \ ,                   "throw"
    \ ,                   "yield"
    \ ,                  ]
    \ , 'jaktBoolean' :["true"
    \ ,                 "false"
    \ ,                ]
    \ , 'jaktKeyword' :["function"
    \ ,                 "extern"
    \ ,                 "import"
    \ ,                ]
    \ , 'jaktException' :["throws"
    \ ,                  ]
    \ , 'jaktMacro' :["defer"
    \ ,               "unsafe"
    \ ,               "try"
    \ ,               "catch"
    \ ,               "cpp"
    \ ,              ]
    \ , 'jaktWordOperator' :["not"
    \ ,                      "and"
    \ ,                      "or"
    \ ,                      "as"
    \ ,                      "in"
    \ ,                     ]
    \ , 'jaktVarDecl' :["mut"
    \ ,                 "let"
    \ ,                 "anon"
    \ ,                 "raw"
    \ ,                ]
    \ , 'jaktType' :["String"
    \ ,              "i8"
    \ ,              "i16"
    \ ,              "i32"
    \ ,              "i64"
    \ ,              "u8"
    \ ,              "u16"
    \ ,              "u32"
    \ ,              "u64"
    \ ,              "f32"
    \ ,              "f64"
    \ ,              "bool"
    \ ,              "c_int"
    \ ,              "c_char"
    \ ,              "usize"
    \ ,              "void"
    \ ,             ]
    \ , 'jaktConstant' :["this"
    \ ,                 ]
    \ , 'jaktStructure' :["struct"
    \ ,                   "class"
    \ ,                   "enum"
    \ ,                   "namespace"
    \ ,                  ]
    \ , 'jaktVisModifier': ["public"
    \ ,                     "private"
    \ ,                    ]
    \ , }

function! s:syntax_keyword(dict)
  for key in keys(a:dict)
    execute 'syntax keyword' key join(a:dict[key], ' ')
  endfor
endfunction

call s:syntax_keyword(s:jakt_syntax_keywords)

syntax match jaktDecNumber display   "\v<\d%(_?\d)*"
syntax match jaktHexNumber display "\v<0x\x%(_?\x)*"
syntax match jaktOctNumber display "\v<0o\o%(_?\o)*"
syntax match jaktBinNumber display "\v<0b[01]%(_?[01])*"

syntax match jaktFatArrowOperator display "\V=>"
syntax match jaktRangeOperator display "\V.."
syntax match jaktOperator display "\V\[-+/*=^&?|!><%~:;,]"

syntax match jaktFunction /\w\+\s*(/me=e-1,he=e-1

syntax match jaktEnumDecl /enum\s\+\w\+/lc=4
syntax match jaktStructDecl /struct\s\+\w\+/lc=6
syntax match jaktClassDecl /class\s\+\w\+/lc=5

syntax region jaktBlock start="{" end="}" transparent fold

syntax region jaktCommentLine start="//" end="$"



syntax region jaktString matchgroup=jaktStringDelimiter start=+"+ skip=+\\\\\|\\"+ end=+"+ oneline contains=jaktEscape
syntax region jaktChar matchgroup=jaktCharDelimiter start=+'+ skip=+\\\\\|\\'+ end=+'+ oneline contains=jaktEscape
syntax match jaktEscape        display contained /\\./

highlight default link jaktDecNumber jaktNumber
highlight default link jaktHexNumber jaktNumber
highlight default link jaktOctNumber jaktNumber
highlight default link jaktBinNumber jaktNumber

highlight default link jaktWordOperator jaktOperator
highlight default link jaktFatArrowOperator jaktOperator
highlight default link jaktRangeOperator jaktOperator

highlight default link jaktStructDecl jaktType
highlight default link jaktClassDecl jaktType
highlight default link jaktEnumDecl jaktType

highlight default link jaktKeyword Keyword
highlight default link jaktType Type
highlight default link jaktCommentLine Comment
highlight default link jaktString String
highlight default link jaktStringDelimiter String
highlight default link jaktChar String
highlight default link jaktCharDelimiter String
highlight default link jaktEscape Special
highlight default link jaktBoolean Boolean
highlight default link jaktConstant Constant
highlight default link jaktNumber Number
highlight default link jaktOperator Operator
highlight default link jaktStructure Structure
highlight default link jaktExecution Special
highlight default link jaktMacro Macro
highlight default link jaktConditional Conditional
highlight default link jaktRepeat Repeat
highlight default link jaktVarDecl Define
highlight default link jaktException Exception
highlight default link jaktFunction Function
highlight default link jaktVisModifier Label

delfunction s:syntax_keyword

let b:current_syntax = "jakt"

let &cpo = s:cpo_save
unlet! s:cpo_save
