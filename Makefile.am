ACLOCAL_AMFLAGS=-I m4
CPPFLAGS=-Iinclude -Ivendor/gtest-1.7.0/include -Ivendor/jsoncpp-0.10.5/dist
check_PROGRAMS = test-program
pkginclude_HEADERS = include/snyder/metrics_registry.h
BUILT_SOURCES = include/snyder/version.h

test_program_SOURCES = tests/test_metrics_registry_counters.cpp tests/test_metrics_registry_gauges.cpp tests/test_metrics_registry.cpp tests/tests.cpp
test_program_LDADD = .libs/libsnyder.a
test_program_LDFLAGS=-Lvendor/gtest-1.7.0/lib/.libs -lgtest

lib_LTLIBRARIES=libsnyder.la
libsnyder_la_SOURCES=source/metrics_registry.cpp
libsnyder_la_CXXFLAGS=$(CXXFLAGS) -fPIC
libsnyder_la_LDFLAGS=-version-info 1:0:1

.PHONY: test check coverage-html docs clean-docs deploy-docs doxygen jekyll include/snyder/version.h

test: check
	./test-program

clean-local:
	find . -name "*.gcda" -print0 | xargs -0 rm

coverage.info: test
	lcov --compat-libtool --capture --directory source --output-file coverage.info
	lcov --compat-libtool --remove coverage.info "/usr*" -o coverage.info

coverage-html: coverage.info
	genhtml -t "snyder coverage report" --legend --show-details coverage.info --output-directory html

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

include/snyder/version.h:
	m4 -I m4 --define=M4_SNYDER_VERSION=$(VERSION) version.h.m4 > $@


GAUGES_CODE="5610468e92c6ac057e0034b0"

doxygen:
	doxygen doxygen.config

jekyll:
	echo "gaugesid: $(GAUGES_CODE)" > docs/_config.yml
	echo "projecturl: $(PROJECT_URL)" >> docs/_config.yml
	echo "basesite: http://www.unwiredcouch.com" >> docs/_config.yml
	echo "markdown: redcarpet" >> docs/_config.yml
	echo "---" > docs/index.md
	echo "layout: project" >> docs/index.md
	echo "title: snyder" >> docs/index.md
	echo "---" >> docs/index.md
	cat README.md >> docs/index.md

docs: doxygen jekyll

clean-docs:
	rm -rf ./docs

deploy-docs: docs
	cd docs && git init && git remote add upstream "https://${GH_TOKEN}@github.com/mrtazz/snyder.git" && \
	git submodule add https://github.com/mrtazz/jekyll-layouts.git ./_layouts && \
	git submodule update --init && \
	git fetch upstream && git reset upstream/gh-pages && \
	git config user.name 'Daniel Schauenberg' && git config user.email d@unwiredcouch.com && \
	touch . && git add -A . && \
	git commit -m "rebuild pages at $(VERSION)" && \
	git push upstream HEAD:gh-pages

