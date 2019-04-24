#! /usr/bin/env python

import sys
from optparse import OptionParser
import random
import math

def convert(size):
    length = len(size)
    lastchar = size[length-1]
    if (lastchar == 'k') or (lastchar == 'K'):
        m = 1024
        nsize = int(size[0:length-1]) * m
    elif (lastchar == 'm') or (lastchar == 'M'):
        m = 1024*1024
        nsize = int(size[0:length-1]) * m
    elif (lastchar == 'g') or (lastchar == 'G'):
        m = 1024*1024*1024
        nsize = int(size[0:length-1]) * m
    else:
        nsize = int(size)
    return nsize


#
# main program
#
parser = OptionParser()
parser.add_option('-s', '--seed',      default=0,     help='semente aleatoria',                                action='store', type='int', dest='seed')
parser.add_option('-a', '--asize',     default='1k',  help='espaco de enderecamento(e.g., 16, 64k, 32m, 1g)',    action='store', type='string', dest='asize')
parser.add_option('-p', '--physmem',   default='16k', help='tamanho da memoria fisica (e.g., 16k, 64k, 32m, 1g)',  action='store', type='string', dest='psize')
parser.add_option('-n', '--addresses', default=5,     help='numero de enderecos virtuais gerados',        action='store', type='int', dest='num')
parser.add_option('-b', '--b',         default='-1',  help='valor do registrador base',                         action='store', type='string', dest='base')
parser.add_option('-l', '--l',         default='-1',  help='valor do registrador bounds',                        action='store', type='string', dest='limit')
parser.add_option('-c', '--compute',   default=False, help='compute as traducoes',                         action='store_true', dest='solve')


(options, args) = parser.parse_args()

print ''
print 'ARG semente aleatoria', options.seed
print 'ARG tamanho do espaco de enderecamento', options.asize
print 'ARG tamanho da memoria fisica', options.psize
print ''

random.seed(options.seed)
asize = convert(options.asize)
psize = convert(options.psize)

if psize <= 1:
    print 'Erro: memoria fisica deve ser positiva.'
    exit(1)

if asize == 0:
    print 'Erro: Espaco de enderecamento deve ser positivo.'
    exit(1)

if psize <= asize:
    print 'Erro: memoria fisica deve ser maior que espaco de enderecamento( nesta simulacao)'
    exit(1)

#
# need to generate base, bounds for segment registers
#
limit = convert(options.limit)
base  = convert(options.base)

if limit == -1:
    limit = int(asize/4.0 + (asize/4.0 * random.random()))

# now have to find room for them
if base == -1:
    done = 0
    while done == 0:
        base = int(psize * random.random())
        if (base + limit) < psize:
            done = 1

print 'Base-and-Bounds:'
print ''
print '  Base   : 0x%08x (decimal %d)' % (base, base)
print '  Bounds  : %d' % (limit)
print ''

if base + limit > psize:
    print 'Erro: espaco de enderecamento nao cabe na memoria fisica com esses valores de base/bounds.'
    print 'Base + Bounds:', base + limit, '  Psize:', psize
    exit(1)

#
# now, need to generate virtual address trace
#
print 'Enderecos virtuais gerados'
for i in range(0,options.num):
    vaddr = int(asize * random.random())
    if options.solve == False:
        print '  VA %2d: 0x%08x (decimal: %4d) --> Endereco Fisico valido ou violacao de segmento?' % (i, vaddr, vaddr)
    else:
        paddr = 0
        if (vaddr >= limit):
            print '  VA %2d: 0x%08x (decimal: %4d) --> FALHA DE SEGMENTACAO' % (i, vaddr, vaddr)
        else:
            paddr = vaddr + base
            print '  VA %2d: 0x%08x (decimal: %4d) --> VALIDO: 0x%08x (decimal: %4d)' % (i, vaddr, vaddr, paddr, paddr)


print ''

if options.solve == False:
    print 'Para cada endereco virtual VA, responda qual endereco fisico ele se traduz'
    print 'OU escreva out-of-bounds para indicar que ouve uma falha de segmentacao (endereco invalido)'
    print 'Neste problema, assuma um espaco de enderecamento virtual de tamanho fixo.'
    print ''





