pkgname="log-console"
epoch=1
pkgver=17
pkgrel=1
pkgdesc="console logger static library"
arch=("x86_64")
url="https://github.com/imperzer0/log-console"
license=('GPL')
# depends=()
makedepends=("cmake>=3.0")

_libfiles=("log-console" "log-console-defs")
_md5sums=("1042a793b5481de07262fccd09e2a2f9" "2fd9a98d504fba82afbc322976c6e4b6")

# add all library files to sources
for _libfile in ${_libfiles[@]}
{
    source=(${source[@]} "local://"$_libfile)
}

# skip all checksums
for _md5sum in ${_md5sums[@]}
{
    md5sums=(${md5sums} _md5sum)
}

# install=log-console.install

package()
{
    for libfile in ${libfiles[@]}
	{
	    install -Dm755 "./$libfile" "$pkgdir/usr/include/$libfile"
	}
}
