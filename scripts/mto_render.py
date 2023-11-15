import fnmatch
import numpy as np
import os
import mto_utils
import matplotlib.pyplot as plt
import matplotlib.animation as animation


INPUT_ARRAY_FORMAT = '.npy'

OUTPUT_MOVIE_FORMAT = '.mp4'

POINT2_TAG = 'point2'
LINE2_TAG = 'line2'

X_TAG = 'x'
Y_TAG = 'y'
Z_TAG = 'z'

video_writer = 'ffmpeg'
video_extra_args = ['-vcodec', 'libx264', '-pix_fmt', 'yuv420p']

def remove_ext(filename):
    """
    Return after #
    Args:
        filename (_type_): _description_

    Returns:
        _type_: _description_
    """
    return filename[:-len(INPUT_ARRAY_FORMAT)]


def parse_tags(filename):
    """
    Split by # and ,
    Args:
        filename (_type_): _description_

    Returns:
        _type_: _description_
    """
    tokens = remove_ext(filename).split("#")
    if len(tokens) > 1:
        return tokens[1].split(",")
    else:
        print("Something error here!\n")

def is_animation(tags):
    """
    Judge whether has a tag : 0000 - 9999 
    Args:
        tags (_type_): _description_

    Returns:
        _type_: _description_
    """
    for tag in tags:
        if fnmatch.filter([tag], '[0-9][0-9][0-9][0-9]'):
            return True
    return False



def get_output_movie_filename(filename):
    return remove_ext(filename.replace(',0000','')) + OUTPUT_MOVIE_FORMAT


def render_line2(filename, frame_rate):
    if is_animation(parse_tags(filename)):
        data = []
        # filename = filename.replace('0000', '%04d' % frame_rate)
        # print(filename)
        
        def get_line_data(filename, frame):
            """
            Return the relate file data according to the param:frame by replace and np.load
            Args:
                filename (_type_): _description_
                frame (_type_): _description_

            Returns:
                _type_: _description_
            """
            filename = filename.replace("0000", f'{frame:04d}')
            data_x = np.load(filename)
            data_y = np.load(filename.replace(',' + X_TAG, "," + Y_TAG))
            return (data_x, data_y)
        
        def update_lines(frame, line):
            x, y = data[frame]
            line.set_data(x, y)
            return line
        # print(get_line_data(filename, frame_rate))
        
        dirname = os.path.dirname(filename) # get the dirname
        basename = os.path.basename(filename).replace("0000", '[0-9][0-9][0-9][0-9]') # get the partern
        seq = mto_utils.get_all_files(dirname, [basename])
        seq.sort()
        
        data_x, data_y = get_line_data(seq[0], 0) # 获取到第0个
        has_bbox = False
        # below for is finding the bbx and collect data
        for frame in range(len(seq)):
            data_x, data_y = get_line_data(seq[frame], frame)
            if has_bbox:
                xmin = min(xmin, data_x.min())
                xmax = max(xmax, data_x.max())
                ymin = min(ymin, data_y.min())
                ymax = max(ymax, data_y.max())
            else:
                xmin = data_x.min()
                xmax = data_x.max()
                ymin = data_y.min()
                ymax = data_y.max()
                has_bbox = True
            data.append((data_x, data_y)) # 获取数据
        # print(data[0])
        
        fig, ax = plt.subplots() # 
        x, y = get_line_data(filename, 0)
        if has_bbox:
            xmid = (xmax + xmin) / 2.0
            ymid = (ymax + ymin) / 2.0
            new_xmin = xmid - 1.25 * (xmid - xmin)
            new_xmax = xmid + 1.25 * (xmax - xmid)
            new_ymin = ymid - 1.25 * (ymid - ymin)
            new_ymax = ymid + 1.25 * (ymax - ymid)
            ax.set_xlim(new_xmin, new_xmax)
            ax.set_ylim(new_ymin, new_ymax) 
        ax.set_aspect('equal') # xy has same scale
        line, = ax.plot(x, y, lw=2, marker='o', markersize=3)
        # print(line.get_xdata())
        anim = animation.FuncAnimation(fig, update_lines, len(seq), fargs=(line, ), interval=60, blit=False)
        output_filename = get_output_movie_filename(filename.replace(',' + X_TAG, ''))
        anim.save(output_filename, fps=frame_rate, bitrate=5000, writer='ffmpeg', extra_args=video_extra_args)
        plt.close(fig)
        print("Rendered<%s>" % output_filename)
        
        # fig_new, axs_new = plt.subplots(3, 3)
        # for i in range(3):
        #     for j in range(3):
        #         ax_new = axs_new[i, j]
        #         ax_new.plot(data[(i+j) * 40][0], data[(i+j) * 40][1])
        # plt.show()
        # plt.show()


if __name__ == "__main__":
    parse_tags('manual_tests_output/PhysicsAnimation/SimpleMassSpringAnimation/data.#line2,0359,x.npy')