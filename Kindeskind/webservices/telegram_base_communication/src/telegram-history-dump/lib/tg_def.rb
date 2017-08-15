# Generated from https://github.com/vysheng/tgl/blob/ffb04caca71de0cddf28cd33a4575922900a59ed/tgl-layout.h
# by substituting /#define ([^ ]+) (.*)/ with '\1 = \2'

module TgDef

  TGLDF_IMAGE = 1
  TGLDF_STICKER = 2
  TGLDF_ANIMATED = 4
  TGLDF_AUDIO = 8
  TGLDF_VIDEO = 16

  TGLMF_UNREAD = 1
  TGLMF_OUT = 2
  TGLMF_DISABLE_PREVIEW = 4
  TGLMF_MENTION = 16
  TGLMF_CREATED = (1 << 8)
  TGLMF_PENDING = (1 << 9)
  TGLMF_DELETED = (1 << 10)
  TGLMF_ENCRYPTED = (1 << 11)
  TGLMF_EMPTY = (1 << 12)
  TGLMF_SERVICE = (1 << 13)
  TGLMF_SESSION_OUTBOUND = (1 << 14)
  TGLMF_POST_AS_CHANNEL = (1 << 8)
  TGLMF_HTML = (1 << 9)

  TGLMF_CREATE = 0x10000


  TGLPF_CREATED = (1 << 0)
  TGLPF_CREATE = 0x80000000
  TGLPF_HAS_PHOTO = (1 << 1)
  TGLPF_DELETED = (1 << 2)
  TGLPF_OFFICIAL = (1 << 3)
  TGLPF_KICKED = (1 << 4)
  TGLPF_ADMIN = (1 << 5)
  TGLPF_CREATOR = (1 << 6)
  TGLPF_LEFT = (1 << 7)
  TGLPF_DEACTIVATED = (1 << 8)

  TGLUF_CONTACT = (1 << 16)
  TGLUF_MUTUAL_CONTACT = (1 << 17)
  TGLUF_BLOCKED = (1 << 18)
  TGLUF_SELF = (1 << 19)
  TGLUF_CREATED = TGLPF_CREATED
  TGLUF_DELETED = TGLPF_DELETED
  TGLUF_HAS_PHOTO = TGLPF_HAS_PHOTO
  TGLUF_CREATE = TGLPF_CREATE
  TGLUF_BOT = (1 << 20)
  TGLUF_OFFICIAL = TGLPF_OFFICIAL

  TGLUF_TYPE_MASK = \
  (TGLUF_CONTACT | TGLUF_MUTUAL_CONTACT | TGLUF_BLOCKED | TGLUF_SELF | TGLUF_CREATED | TGLUF_DELETED | TGLUF_OFFICIAL)

  TGLCF_CREATED = TGLPF_CREATED
  TGLCF_CREATE = TGLPF_CREATE
  TGLCF_HAS_PHOTO = TGLPF_HAS_PHOTO
  TGLCF_KICKED = TGLPF_KICKED
  TGLCF_CREATOR = TGLPF_CREATOR
  TGLCF_ADMIN = TGLPF_ADMIN
  TGLCF_OFFICIAL = TGLPF_OFFICIAL
  TGLCF_LEFT = TGLPF_LEFT
  TGLCF_DEACTIVATED = TGLPF_DEACTIVATED
  TGLCF_ADMINS_ENABLED = (1 << 16)

  TGLCF_TYPE_MASK = \
  (TGLCF_CREATED | TGLCF_KICKED | TGLCF_CREATOR | TGLCF_ADMIN | TGLCF_OFFICIAL | TGLCF_LEFT | TGLCF_DEACTIVATED | TGLCF_ADMINS_ENABLED)

  TGLECF_CREATED = TGLPF_CREATED
  TGLECF_CREATE = TGLPF_CREATE
  TGLECF_HAS_PHOTO = TGLPF_HAS_PHOTO
  TGLECF_KICKED = TGLPF_KICKED
  TGLECF_CREATOR = TGLPF_CREATOR
  TGLECF_ADMIN = TGLPF_ADMIN

  TGLECF_TYPE_MASK = \
  (TGLECF_CREATED | TGLECF_KICKED | TGLECF_CREATOR | TGLECF_ADMIN)

  TGLCHF_CREATED = TGLPF_CREATED
  TGLCHF_CREATE = TGLPF_CREATE
  TGLCHF_HAS_PHOTO = TGLPF_HAS_PHOTO
  TGLCHF_KICKED = TGLPF_KICKED
  TGLCHF_CREATOR = TGLPF_CREATOR
  TGLCHF_ADMIN = TGLPF_ADMIN
  TGLCHF_OFFICIAL = TGLPF_OFFICIAL
  TGLCHF_LEFT = TGLPF_LEFT
  TGLCHF_DEACTIVATED = TGLPF_DEACTIVATED
  TGLCHF_BROADCAST = (1 << 16)
  TGLCHF_EDITOR = (1 << 17)
  TGLCHF_MODERATOR = (1 << 18)
  TGLCHF_MEGAGROUP = (1 << 19)

  TGLCHF_TYPE_MASK = \
  (TGLCHF_CREATED | TGLCHF_KICKED | TGLCHF_CREATOR | TGLCHF_ADMIN | TGLCHF_OFFICIAL | TGLCHF_LEFT | TGLCHF_DEACTIVATED | TGLCHF_BROADCAST | TGLCHF_EDITOR | TGLCHF_MODERATOR | TGLCHF_MEGAGROUP)


  TGLCHF_DIFF = 0x20000000

  TGL_FLAGS_UNCHANGED = 0x40000000

  TGLDCF_AUTHORIZED = 1
  TGLDCF_LOGGED_IN = 8

  TGL_PERMANENT_ID_SIZE = 24

end