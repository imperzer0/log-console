pkgname="log-console"
epoch=1
pkgver=17
pkgrel=0
pkgdesc="console logger static library"
arch=("x86_64")
url="https://github.com/imperzer0/log-console"
license=('GPL')
# depends=()
makedepends=("cmake>=3.0")

libfiles=("log-console" "log-console-defs")

# add all library files to sources
for libfile in ${libfiles[@]}
{
    source=(${source[@]} "local://"$libfile)
}

# skip all checksums
for libfile in ${libfiles[@]}
{
    md5sums=(${md5sums} "SKIP")
}

# install=log-console.install

package()
{
    for libfile in ${libfiles[@]}
	{
	    install -Dm755 "./$libfile" "$pkgdir/usr/include/$libfile"
	}
}
