import mto_render
import mto_utils
import argparse

# 添加一个-f参数，返回一个命名空间对象
def processArguments():
    parser = argparse.ArgumentParser(   
        description="Hello! You need to run this python file from the same level as the manual_tests_output directory."
    )
    parser.add_argument("-f", "--fps", type=int, help="update a new frame rate(default is 60fps)")
    return parser.parse_args()
# 返回命名空间参数中的fps
def getFrameRate(arguments):
    if arguments.fps:
        fps = arguments.fps
    else:
        fps = 60
    return fps

if __name__ == "__main__":
    
    fps = getFrameRate(processArguments()) # 返回通过参数输入的fps
    filenames = mto_utils.get_all_files("manual_tests_output",["*" + mto_render.INPUT_ARRAY_FORMAT])
    filenames.sort()
    
    for filename in filenames:
        try:
            tags = mto_render.parse_tags(filename)

            if mto_render.Y_TAG in tags or mto_render.Z_TAG in tags: # 排除 yz
                continue
            if mto_render.is_animation(tags) and '0000' not in tags: # 只要0000
                continue
            if mto_render.POINT2_TAG in tags:
                pass
            elif mto_render.LINE2_TAG in tags: 
                mto_render.render_line2(filename, fps) # 渲染 line2
        except Exception as e:
            print("Failed to render.")