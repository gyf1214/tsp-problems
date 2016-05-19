require 'opencv'
include OpenCV

raise if ARGV[0].nil?

@margin = 50
@width = 640

def pre
  input = File.read(ARGV[0] + '/in').split "\n"
  @nCity = input.slice!(0).to_i
  @cities = Array.new
  xs = Array.new
  ys = Array.new
  input.each do |line|
    x, y = line.split.map &:to_f
    @cities.push [x, y]
    xs.push x
    ys.push y
  end
  @left, @right = xs.min, xs.max
  @bottom, @top = ys.min, ys.max
  @right -= @left
  @top -= @bottom
  @height = (@width / @right * @top).round
  @cities.map! { |e| trans e }
end

def trans point
  x, y = point
  nx = (1 - (x - @left) / @right) * @width + @margin
  ny = (y - @bottom) / @top * @height + @margin
  [nx, ny].map &:round
end

def draw seq, ret
  l = seq.last
  ret.set! CvColor::White
  seq.each do |x|
    u, v = @cities[l], @cities[x]
    ret.line! CvPoint.new(u[1], u[0]), CvPoint.new(v[1], v[0]), color: CvColor::Black
    l = x
  end
end

def endSeq path
  input = `tail -2 #{ARGV[0]}/#{path}`.split("\n")[0]
  input ||= ""
  input.split.map &:to_i
end

pre

ARGV[1] ||= 'out'

window = GUI::Window.new "hello"

@img = CvMat.new @width + 2 * @margin, @height + 2 * @margin, CV_8UC1
@img.set! CvColor::White

window.show @img

loop do
  draw endSeq(ARGV[1]), @img
  window.show @img
  GUI::wait_key 100
end
