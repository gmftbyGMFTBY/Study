sentence = input("Input:")
box_wid = len(sentence)
all_wid = 80
margin_wid = (all_wid - box_wid)//2
print('-'*all_wid)
print(' '*all_wid)
print(' '*margin_wid+'|'+sentence+'|'+' '*margin_wid)
print(' '*all_wid)
print('-'*all_wid)
