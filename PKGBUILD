pkgname="log-console"
epoch=1
pkgver=12
pkgrel=2
pkgdesc="console logger static library"
arch=("x86_64")
url="https://github.com/imperzer0/log-console"
license=('GPL')
# depends=()
makedepends=("cmake>=3.0")
source=("local://log-console")
md5sums=("SKIP")
# install=log-console.install

package()
{
	install -Dm755 "./$pkgname" "$pkgdir/usr/include/$pkgname"
}
