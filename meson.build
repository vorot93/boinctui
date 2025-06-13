project('boinctui', 'cpp', version: '2.7.1', default_options: ['cpp_std=c++11'])

boinctui_deps = [
  dependency('ncursesw'),
  dependency('panelw'),
  dependency('formw'),
  dependency('menuw'),
  dependency('expat'),
]

add_project_arguments('-DENABLEMOUSE', language: 'cpp')
add_project_arguments('-DNCURSES_INTERNALS', language: 'cpp')

if get_option('without-gnutls')
  boinctui_deps += dependency('openssl')
  add_project_arguments('-DHAVE_OPENSSL', language: 'cpp')
else
  boinctui_deps += dependency('gnutls')
endif

boinc_dir = get_option('boinc_dir')
add_project_arguments('-DBOINC_DIR="@0@"'.format(boinc_dir), language: 'cpp')

subdir('src')
