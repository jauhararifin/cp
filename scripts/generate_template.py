import argparse


def file_lines(filename, flag='r'):
    with open(filename, flag) as f:
        return f.readlines()


class TemplateFileReader(object):

    def __init__(self, writer, region_name):
        self.writer = writer   
        self.region_name = region_name

    def read_file(self, file_name):
        inside_region = False
        for line in file_lines(file_name):
            start_reg_name = self.get_start_region_name(line)
            if start_reg_name == self.region_name:
                inside_region = True
                continue

            end_reg_name = self.get_end_region_name(line)
            if inside_region and end_reg_name == self.region_name:
                inside_region = False
                continue

            if inside_region:
                self.writer.write(line) 

    def get_start_region_name(self, line):
        arr = line.split()
        if len(arr) < 3 or arr[0] != '#pragma' or arr[1] != 'region':
            return None
        return arr[2]


    def get_end_region_name(self, line):
        arr = line.split()
        if len(arr) < 3 or arr[0] != '#pragma' or arr[1] != 'endregion':
            return None
        return arr[2]


def generate_template_source_code(template_file_name, output_file_name, region_name, template_items):
    with open(output_file_name, 'w') as f_output:
        template_fr = TemplateFileReader(f_output, region_name)
        for temp_line in file_lines(template_file_name):
            if temp_line.split() == ['#pragma', 'template']:
                f_output.write('#pragma region %s\n' % region_name)
                for temp_it in template_items:
                    template_fr.read_file(temp_it)
                f_output.write('#pragma endregion %s\n' % region_name)
            else:
                f_output.write(temp_line)

def run():
    ap = argparse.ArgumentParser()

    ap.add_argument("-t", "--template", required=True, help="the template file")
    ap.add_argument("-o", "--output", required=True, help="output file")
    ap.add_argument("-r", "--region", required=True, help="region name")
    ap.add_argument('template_items', metavar='item', type=str, nargs='+', help='template item file names')
    args = vars(ap.parse_args())
    
    generate_template_source_code(
        args['template'],
        args['output'],
        args['region'],
        args['template_items'],
    ) 

if __name__ == '__main__':
    run()
