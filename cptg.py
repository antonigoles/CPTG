import xml.etree.ElementTree as ET
import random
import string


def get_deafult_value(value, deafult_value):
    """Returns value if value is not NoneType. If value is None returns deafult_value."""
    return value if value is not None else deafult_value

def handle_const(element: ET.Element) -> str:
    '''Handles the const tag. Returns the value of the const and a regular space.'''
    return element.attrib['value']+" "

def handle_br(element: ET.Element) -> str:
    '''Handles the br tag. Returns a new line char.'''
    return "\n"

def handle_seq(element: ET.Element) -> str:
    '''Handles the seq tag by looping and calling handle_tag function.'''
    
    return_str = ""


    repeatitons = int(get_deafult_value(element.attrib.get('times'), 1))
    
    for i in range(repeatitons):
        for i in element:
            return_str += handle_tag(i)

    return return_str


var_char_translation_dict = {
    'abc' : string.ascii_lowercase,
    'ABC' : string.ascii_uppercase,
    'special' : string.punctuation.replace("`", ""),      # The tick (`) is removed to meet the specifications
    'all' : string.ascii_lowercase + string.ascii_uppercase + string.punctuation.replace("`", "")
}

def handle_var_char(element: ET.Element) -> str:
    '''Handles the char type of var tag. Generates a random char.'''
    contents = get_deafult_value(element.attrib.get('range'), 'abc')

    return "".join(random.choice(var_char_translation_dict[contents]))+" "

def handle_var_string(element: ET.Element) -> str:
    '''Handles the string type of var tag. Generates a random string.'''
    length = int(get_deafult_value(element.attrib.get('length'), 3))
    contents = get_deafult_value(element.attrib.get('range'), 'abc')

    return "".join(random.choices(var_char_translation_dict[contents], k=length))+" "

def handle_var_number(element: ET.Element) -> str:
    '''Handles the number type of var tags. Generates a random int.'''
    value_range = get_deafult_value(element.attrib.get('range'), '0:9')

    n1, n2 = value_range.split(":")      # Converts string range to a pair of numbers
    return str(random.randint(int(n1), int(n2)))+" "

def handle_var_float(element: ET.Element) -> str:
    '''Handles the float type of var tags. Generates a random number with a given number of places after the decimal point.'''
    length = int(get_deafult_value(element.attrib.get('length'), 3))
    value_range = get_deafult_value(element.attrib.get('range'), '0:9')

    n1, n2 = value_range.split(":")     # Converts string range to a pair of numbers
    return str(random.randint(int(n1)* 10**length, int(n2)* 10**length) / 10**length)+" "  # Multiplication and division is used instead of round() to ensure better distribution


var_function_dict = {
    'Char' : handle_var_char,
    'Number' : handle_var_number,
    'Float' : handle_var_float,
    'String' : handle_var_string
}

def handle_var(element: ET.Element) -> str:
    '''Handles the var tag by calling a seperate function for each of the types'''
    type = get_deafult_value(element.attrib.get('type'), 'Number')
    return var_function_dict[type](element)


tag_function_dict = {
    'const' : handle_const,
    'br' : handle_br,
    'var' : handle_var,
    'seq' : handle_seq
    }

def handle_tag(element: ET.Element) -> str:
    '''A common function called to handle any tag. Its job is to call one of the specific funtions, based on the given tag'''
    return tag_function_dict[element.tag](element)




def generate_test(filepath: str) -> str:
    '''Generates a singular test based on a XML file to which a filepath is provided. Returns it as a str'''

    # defines a string to which values will be appended
    final_str = ""

    # imports xml file
    tree = ET.parse(filepath)
    root = tree.getroot()

    # checks if XML file is a CPTG file
    if root.tag != 'test':
        raise Exception("XML file not meeting CPTG specification")

    for element in root:
        final_str += handle_tag(element)


    return final_str





if __name__ == '__main__':
    import argparse

    # Parsing of command line arguments
    parser = argparse.ArgumentParser()

    parser.add_argument('input_filepath', type=str, help='Filepath to xml file containing generation instructions')
    parser.add_argument('output_filepath', type=str, help='Filepath to output file containing the test')

    args = parser.parse_args()

    # generating the test
    test = generate_test(args.input_filepath)

    # and writing it to the file
    with open(args.output_filepath, "w") as file:
        file.write(test)