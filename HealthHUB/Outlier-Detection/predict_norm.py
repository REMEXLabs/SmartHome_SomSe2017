import sys, ast, getopt, types

import pickle
import numpy as np

def main(data):
    if not data:
        print ("No Data was passed")
        sys.exit(2)  
    
    preprocessor = pickle.load(open('preprocessor.pickle', 'rb'))
    model = pickle.load(open('model.pickle', 'rb'))

    data = np.asarray(data).reshape(1, -1)
    data = preprocessor.transform(data)

    print(model.predict(data))

def prepare_argv(argv):
    data = None
    arg_dict={}
    switches={'li':list}
    singles=''.join([x[0]+':' for x in switches])
    long_form=[x+'=' for x in switches]
    d={x[0]+':':'--'+x for x in switches}
    try:            
        opts, args = getopt.getopt(argv, singles, long_form)
    except getopt.GetoptError:          
        print ("bad arg")
        sys.exit(2)   

    for opt, arg in opts:        
        if opt[1]+':' in d: o=d[opt[1]+':'][2:]
        elif opt in d.values(): o=opt[2:]
        else: o =''
        if o and arg:
            data=ast.literal_eval(arg)
    return data

if __name__ == "__main__":
       data = prepare_argv(sys.argv[1:])
       main(data)