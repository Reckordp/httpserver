SUMBER = Dir.glob("src/*.c")
TUJUAN = "server.exe"
INCLUDE_JALUR = %w( include )
WINDOWSOPTS = "-lws2_32"

OBJFILE = SUMBER.collect do |s|
  obj = s.sub(/\.c$/, '.o')
  obj.sub(/^src/, 'build')
end
GETSRC = proc do |task_name|
  name = task_name.sub(/^build/, 'src')
  name.sub(/.o$/, '.c')
end

rule '.o' => GETSRC do |t|
  include_opt = INCLUDE_JALUR.collect { |i| "-I " + i } .join(' ')
  sh "gcc #{include_opt} -o #{t.name} -c #{t.prerequisites.first}"
end

file TUJUAN => OBJFILE do
  sh "gcc #{OBJFILE.join(" ")} #{WINDOWSOPTS} -o #{TUJUAN}"
end

task :clean do 
  sh 'rmdir /S /Q build'
  sh 'del ' + TUJUAN
end

Dir.mkdir('build') unless Dir.exist?('build')
task default: TUJUAN