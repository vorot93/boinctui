FROM alpine AS base

RUN \
    apk add \
        automake autoconf g++ make \
        ncurses-dev expat-dev openssl-dev

COPY ./ /workdir/
WORKDIR /workdir

RUN \
    meson setup builddir -D without-gnutls=true; \
    meson compile -C builddir; \
    strip builddir/src/boinctui

FROM alpine AS final

RUN \
    apk add --no-cache \
        expat ncurses openssl libstdc++ \
        libpanelw libformw libmenuw

COPY --from=base /workdir/builddir/src/boinctui /
ENTRYPOINT ["/boinctui"]
