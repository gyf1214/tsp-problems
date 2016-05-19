require 'opencv'
include OpenCV

raise if ARGV[0].nil?

@margin = 50
@height = 500

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
  @top, @bottom = ys.min, ys.max
  @right -= @left
  @bottom -= @top
  @width = (@height / @bottom * @right).round
  @cities.map! { |e| trans e }
end

def trans point
  x, y = point
  nx = (x - @left) / @right * @width + @margin
  ny = (y - @top) / @bottom * @height + @margin
  [nx, ny].map &:round
end

def draw seq
  l = seq.last
  ret = CvMat.new @height + 2 * @margin, @width + 2 * @margin, CV_8UC1
  ret.set! CvColor::White
  seq.each do |x|
    u, v = @cities[l], @cities[x]
    ret.line! CvPoint.new(u[0], u[1]), CvPoint.new(v[0], v[1]), color: CvColor::Black
    l = x
  end
  ret
end

def endSeq
  input = File.read(ARGV[0] + '/out').split("\n")[0]
  input.split.map &:to_i
end

pre

img = draw endSeq

window = GUI::Window.new ""
window.show img
GUI::wait_key
