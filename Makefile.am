ACLOCAL_AMFLAGS=-I m4
CPPFLAGS=-Iinclude -Ivendor/gtest-1.7.0/include -Ivendor/jsoncpp-0.10.5/dist
check_PROGRAMS = test-program
pkginclude_HEADERS = include/snyder/metrics_registry.h

test_program_SOURCES = tests/test_metrics_registry_counters.cpp tests/test_metrics_registry_gauges.cpp tests/tests.cpp
test_program_LDADD = .libs/libsnyder.a
test_program_LDFLAGS=-Lvendor/gtest-1.7.0/lib/.libs -lgtest

lib_LTLIBRARIES=libsnyder.la
libsnyder_la_SOURCES=source/metrics_registry.cpp
libsnyder_la_CXXFLAGS=-fPIC
libsnyder_la_LDFLAGS=-version-info 1:0:1

.PHONY: test check clean-coverage-files coverage-html

test: check
	./test-program

clean-local:
	find . -name "*.gcda" -print0 | xargs -0 rm

coverage.info: test
	./utils/lcov-1.11/bin/lcov --compat-libtool --capture --directory source --output-file coverage.info
	./utils/lcov-1.11/bin/lcov --compat-libtool --remove coverage.info "/usr*" -o coverage.info

coverage-html: coverage.info
	./utils/lcov-1.11/bin/genhtml -t "snyder coverage report" --legend --show-details coverage.info --output-directory html

local-install:
	$(MAKE) install PREFIX=usr

NAME=snyder
VERSION = $(shell git describe --tags --always --dirty)
BUILDER = $(shell echo "`git config user.name` <`git config user.email`>")
PKG_RELEASE ?= 1
PROJECT_URL="https://github.com/mrtazz/$(NAME)"
FPM_FLAGS= --name $(NAME) --version $(VERSION) --iteration $(PKG_RELEASE) --epoch 1 --license MIT --maintainer "$(BUILDER)" --url $(PROJECT_URL) --vendor mrtazz usr

rpm:
	  fpm -t rpm -s dir $(FPM_FLAGS)

deb:
	  fpm -t deb -s dir $(FPM_FLAGS)

packages: local-install rpm deb
