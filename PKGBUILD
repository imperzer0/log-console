pkgname="log-console"
pkgver=1.18
pkgrel=1
pkgdesc="console logger static library"
arch=("x86_64")
author="imperzer0"
branch="master"
url="https://github.com/$author/$pkgname"
license=('GPL')

_srcprefix="local:/"
_libfiles=("$pkgname" "$pkgname""-defs")
md5sums=("a727176f5d208daceb4a9aab4b15cfad" "2fd9a98d504fba82afbc322976c6e4b6")

# add all library files to sources
for _libfile in ${_libfiles[@]}
{
    source=(${source[@]} "$_srcprefix/"$_libfile)
}

package()
{
    for _libfile in ${_libfiles[@]}
	{
	    install -Dm755 "./$_libfile" "$pkgdir/usr/include/$_libfile"
	}
}
