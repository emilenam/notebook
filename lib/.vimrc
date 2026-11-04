/* -
name = "Vim"
[info]
- */
set cin aw is et ts=2 sw=2 nu bg=dark cb=unnamedplus mouse=a hlsearch
sy on
ino {<CR> {<CR>}<Esc>ko
ca Hash w !cpp -dD -P -fpreprocessed \| tr -d '[:space:]' \| md5sum \| cut -c-6
tmap <Esc><Esc> <C-\><C-N>
nmap <Esc> <cmd>noh<CR>
nmap [<Space> m`O<Esc>d0``
nmap ]<Space> m`o<Esc>d0``
