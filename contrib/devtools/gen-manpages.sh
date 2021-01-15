#!/usr/bin/env bash

export LC_ALL=C
TOPDIR=${TOPDIR:-$(git rev-parse --show-toplevel)}
BUILDDIR=${BUILDDIR:-$TOPDIR}

BINDIR=${BINDIR:-$BUILDDIR/src}
MANDIR=${MANDIR:-$TOPDIR/doc/man}

SYSCOIND=${SYSCOIND:-$BINDIR/virclesd}
SYSCOINCLI=${SYSCOINCLI:-$BINDIR/vircles-cli}
SYSCOINTX=${SYSCOINTX:-$BINDIR/vircles-tx}
WALLET_TOOL=${WALLET_TOOL:-$BINDIR/vircles-wallet}
SYSCOINQT=${SYSCOINQT:-$BINDIR/qt/vircles-qt}

[ ! -x $SYSCOIND ] && echo "$SYSCOIND not found or not executable." && exit 1

# The autodetected version git tag can screw up manpage output a little bit
read -r -a SYSVER <<< "$($SYSCOINCLI --version | head -n1 | awk -F'[ -]' '{ print $6, $7 }')"

# Create a footer file with copyright content.
# This gets autodetected fine for virclesd if --version-string is not set,
# but has different outcomes for vircles-qt and vircles-cli.
echo "[COPYRIGHT]" > footer.h2m
$SYSCOIND --version | sed -n '1!p' >> footer.h2m

for cmd in $SYSCOIND $SYSCOINCLI $SYSCOINTX $WALLET_TOOL $SYSCOINQT; do
  cmdname="${cmd##*/}"
  help2man -N --version-string=${SYSVER[0]} --include=footer.h2m -o ${MANDIR}/${cmdname}.1 ${cmd}
  sed -i "s/\\\-${SYSVER[1]}//g" ${MANDIR}/${cmdname}.1
done

rm -f footer.h2m
