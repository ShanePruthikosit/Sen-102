import datetime

class ImmigrationRecord:
    def __init__(self, passport, name, date):
        self.passport = passport
        self.name = name
        self.date = date

def get_string(prompt_message):
    while True:
        user_input = input(prompt_message).strip()
        if user_input:
            return user_input
        print("Please input a valid string.")

def validate_int(input_str):
    try:
        int(input_str)
        return True
    except ValueError:
        return False

def validate_float(input_str):
    try:
        float(input_str)
        return True
    except ValueError:
        return False

def field_check(token_count):
    if token_count == 3:
        return True
    elif token_count < 3:
        print(f"Only {token_count} fields found - skipping\n")
    else:
        print(f"{token_count} fields found - skipping\n")
    return False

def print_options():
    print("Available options:")
    print("1 - Search for a passport number")
    print("2 - Add Traveler")
    print("3 - Exit")

def validate_input(input_str):
    return input_str.isdigit()

def get_int():
    while True:
        print_options()
        user_input = input("Enter your choice: ")
        if validate_input(user_input):
            return int(user_input)
        print("Please input a valid integer.")

def find_passport(passport_num, record_array):
    found = False
    for record in record_array:
        if record.passport == passport_num:
            print(f"{record.passport} {record.name} {record.date}")
            found = True
            break
    if not found:
        print("No passports found\n")

def get_date():
    return datetime.datetime.now().strftime("%Y-%m-%d")

def main():
    input_file = input("Name of input file with immigration data (text file)? ")
    with open(input_file, "r") as file:
        array_size = int(file.readline())
        record_array = []
        for line in file:
            tokens = line.strip().split(',')
            if field_check(len(tokens)):
                record_array.append(ImmigrationRecord(tokens[0], tokens[1], tokens[2]))

    option = get_int()
    while option != 3:
        if option == 1:
            passport = get_string("Enter passport number: ")
            find_passport(passport, record_array)
        elif option == 2:
            unique = False
            name = get_string("Enter name: ")
            date = get_date()
            while not unique:
                passport = get_string("Enter a valid passport number: ")
                if len(passport) > 12 and len(passport) < 16:
                    unique = True
                for record in record_array:
                    if record.passport == passport:
                        print("Passport number already exists. Please enter a unique passport number.")
                        break
            record_array.append(ImmigrationRecord(passport, name, date))
        option = get_int()

    with open(input_file, "w") as file:
        file.write(str(len(record_array)) + "\n")
        for record in record_array:
            file.write(f"{record.passport},{record.name},{record.date}\n")

if __name__ == "__main__":
    main()
