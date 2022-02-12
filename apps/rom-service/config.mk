#
# -- This is ROM! --
#
# Vectors placed at 0x0000 to 0x0080
# Code segment placed at 0x0080 to 0x3FFF
# Data segment may be placed 0x4000  to 0xFFFF by STARTDATA
# Stack placed after DATA segment and staxk size is SSIZE

# Start of data segment
STARTDATA=0xC000

# Stack size
SSIZE=0x0400
