import csv

execution = True


def check_win(current_num, special_price, grand_price, regular_prices, sixth_prices):
    assert len(current_num) == 8
    assert current_num.isdigit(), "The current number contained alphabetic characters: {}".format(current_num)
    assert len(special_price) == 8
    assert len(grand_price) == 8
    assert all([len(x) == 8 for x in regular_prices])
    assert all([len(x) == 3 for x in sixth_prices])

    current_num = str(current_num)

    # Special price
    if current_num == special_price:
        print("Your number {} won the special price!".format(current_num))
        return

    # Grand price
    if current_num == grand_price:
        print("Your number {} won the grand price!".format(current_num))
        return

    # Regular prices
    for price in regular_prices:
        if current_num == price:
            print("Your number {} won the regular price!".format(current_num))
            return

    global execution
    execution = True

    # Second price
    check_last_n(current_num, 7, regular_prices, 'second price')
    if not execution:
        return

    # Third price
    check_last_n(current_num, 6, regular_prices, 'third price')
    if not execution:
        return

    # Fourth price
    check_last_n(current_num, 5, regular_prices, 'fourth price')
    if not execution:
        return

    # Fifth price
    check_last_n(current_num, 4, regular_prices, 'fifth price')
    if not execution:
        return

    # Sixth price
    check_last_n(current_num, 3, regular_prices, 'sixth price')
    if not execution:
        return

    # Additional sixth price
    check_last_n(current_num, 3, sixth_prices, 'additional sixth price')


def check_last_n(current_num, n, regular_prices, price_title):
    global execution

    for price in regular_prices:
        if current_num[-n:] == price[-n:]:
            print(
                "Your number {} won the ".format(
                    current_num) + price_title + " matching the last " + str(
                    n) + " digits of the number {}!".format(price))
            execution = False
            return


special_price = '12342126'
grand_price = '80740977'
regular_prices = ['36822639', '38786238', '87204837']
sixth_prices = ['991', '715']

if __name__ == '__main__':

    with open('prices.csv', 'r') as f:
        reader = csv.reader(f)
        numbers = list(reader)
    numbers = [n[0] if len(n) > 0 else "" for n in numbers]

    for number in numbers:
        if len(number) > 0:
            check_win(number, special_price, grand_price, regular_prices, sixth_prices)
