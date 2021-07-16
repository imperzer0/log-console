pkgname="log-console"
epoch=1
pkgver=2
pkgrel=1
pkgdesc="console logger static library"
arch=("x86_64")
url="https://github.com/imperzer0/log-console"
license=('GPL')
# depends=()
makedepends=("cmake>=3.0")
source=("local://CMakeLists.txt" "local://log-console" "local://log-console.cpp")
md5sums=("SKIP" "SKIP" "SKIP")
# install=log-console.install

build()
{
	cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_C_COMPILER=gcc -DCMAKE_CXX_COMPILER=g++ .
	make
}

package()
{
	install -Dm755 "./$pkgname" "$pkgdir/usr/lib/$pkgname"
# 	install -Dm755 ""
}
