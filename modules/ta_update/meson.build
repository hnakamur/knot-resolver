# LUA module: ta_update
# SPDX-License-Identifier: GPL-3.0-or-later

config_tests += [
  ['ta_update', files('ta_update.test.lua'), ['snowflake']],
]

integr_tests += [
  # NOTE: ta_update may pass in cases when it should fail due to race conditions
  # To ensure reliability, deckard should introduce a time wait
  ['ta_update', meson.current_source_dir() / 'ta_update.test.integr'],
  ['ta_update.unmanagedkey', meson.current_source_dir() / 'ta_update.unmanagedkey.test.integr'],
]

lua_mod_src += [
  files('ta_update.lua'),
]

install_data(
  install_dir: modules_dir / 'ta_update',
)
