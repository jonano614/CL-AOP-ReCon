

import os
import sys
from pathlib import Path
import re 

def has_cyrillic(text):
    return bool(re.search('[а-яА-ЯёЁ]', text))

def has_ident(text):
    return bool(re.search('[A-Za-z\\d_]', text))


def check_ident(s):
    words = s.split()

    for w in words:
        w  = w.replace("\\n", "\n")
        if has_cyrillic(w) and has_ident(w):
            print(f'like ident: "{w}"')
            return True
    return False

def check_file(path, search_ident):
    if not path.endswith('.c'):
        print(f'skip file {path}')
        return
    data = None
    with open(path) as f:
        data = f.read()
    state = 'init'
    br_count = 0
    i = 0
    string_start = None
    cur_literal = None
    sz = len(data)
    skip_start = None
    skip_next = False
    skip_fname = None
    skip_functions = []
    if not search_ident:
        skip_functions = ['AddQuestUserData', 'Log_QuestInfo', 'Log_TestInfo']
    while i < sz:
        if state == 'init':
            if data[i:].startswith('//'):
                end_edx = data[i:].find("\n")
                if end_edx == -1:
                    break
                i += end_edx
            elif data[i:].startswith('/*'):
                end_edx = data[i+2:].find("*/")
                if end_edx == -1:
                    print("\t\t", f'unable to found end of comment {path}')
                    break
                i += end_edx + 2
                i += 1
            #elif data[i:].startswith('case "'): #data[i:].startswith('.name == "') or data[i:].startswith('.lastname == "') or 
            #    skip_next = True
            elif data[i] == '"':
                state = 'string'
                string_start = i + 1
            else:
                for fname in skip_functions:
                    if data[i:].startswith(fname):
                        i += len(fname)
                        skip_start = i
                        i -= 1
                        state = 'skip_func'
                        skip_fname = fname
                        break
        elif state == 'string':
            if data[i] == '"':
                state = 'init'
                cur_literal = data[string_start:i]
                if search_ident:
                    if check_ident(cur_literal):
                        print("\t\t", f'russian in ident {path}: "{cur_literal}"')
                else:
                    if skip_next:
                        skip_next = False
                    else:
                        if has_cyrillic(cur_literal):
                            print("\t\t", f'russian in {path}: "{cur_literal}"')
        elif state == 'skip_func':
            if data[i] == '(':
                br_count += 1
            elif data[i] == ')':
                br_count -= 1
                if br_count == 0:
                    state = 'init'
                    cur_sk = data[skip_start:i]
                    #print("\t\t", f'skipped {path}: "{skip_fname}{cur_sk}"')
            elif data[i] == '"':
                state = 'skip_string'
        elif state == 'skip_string':
            if data[i] == '"':
                state = 'skip_func'
           
        


        i += 1

if __name__ == '__main__':
    search_ident = False

    if len(sys.argv) == 2:
        param = sys.argv[1]
        if param == '-i' :
            search_ident = True
    for (dirpath, dirnames, filenames) in os.walk('.'):
        for filename in filenames:
            path = os.path.join(dirpath, filename)

            check_file(path, search_ident)



