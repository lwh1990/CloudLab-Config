" Configuration file for vim
set modelines=0		" CVE-2007-2438

" Normally we use vim-extensions. If you want true vi-compatibility
" remove change the following statements
"set nocompatible	" Use Vim defaults instead of 100% vi compatibility
set backspace=2		" more powerful backspacing

" Don't write backup file if vim is being called by "crontab -e"
au BufWrite /private/tmp/crontab.* set nowritebackup nobackup
" Don't write backup file if vim is being called by "chpass"
au BufWrite /private/etc/pw.* set nowritebackup nobackup

syntax on
set number
set ruler
set mouse=a
set noswapfile
set laststatus=2

" tab settings
set smarttab
set tabstop=4
set shiftwidth=4
set softtabstop=4
set expandtab
autocmd FileType makefile,html,xml,php set noexpandtab
autocmd FileType ruby,html,xml,xhtml,php set ts=2 | set sw=2 | set sts=2

" indent settings
set autoindent
set smartindent
set cindent

" taglist
let Tlist_Ctags_Cmd='/usr/local/bin/ctags'
let Tlist_Show_One_File=1    "只显示当前文件的tags
let Tlist_WinWidth=40        "设置taglist宽度
let Tlist_Exit_OnlyWindow=1  "tagList窗口是最后一个窗口，则退出Vim
let Tlist_Use_Right_Window=1 "在Vim窗口右侧显示taglist窗口

"搜索逐字符高亮
set hlsearch
set incsearch

" 高亮当前行
colo desert
"set colorcolumn=81
"set t_Co=256
set cursorline
"hi CursorLine  cterm=NONE   ctermbg=darkred ctermfg=white
"hi CursorColumn cterm=NONE ctermbg=darkred ctermfg=white 

" visual tab
vnoremap <tab> >gv
vnoremap <s-tab> <gv

" FORTRAN support
let fortran_free_source=1
let fortran_have_tabs=1
let fortran_more_precise=1
let fortran_do_enddo=1

set clipboard=unnamed
