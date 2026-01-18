wsf_inc = include_directories('../src')

executable(
  'wsf',
  ['wsf.c', '../src/wsf_config.c', '../src/wsf_proc.c'],
  include_directories: wsf_inc,
  dependencies: [dl_dep],
  c_args: [wsf_libdir_define],
  install: true,
  install_dir: join_paths(get_option('prefix'), get_option('bindir'))
)
