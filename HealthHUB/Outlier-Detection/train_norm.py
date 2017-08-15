import sys, ast, getopt, types
import numpy as np

from sklearn.covariance import EllipticEnvelope
from sklearn import preprocessing
import pickle

def main(data = []):
    if not data or len(data) < 12:
        print ("Data with at least 12 entries is needed to ensure a meaningful result")
        sys.exit(2)    

    scaler = preprocessing.StandardScaler().fit(data)
    data = scaler.transform(data)

    pickle.dump(scaler, open('preprocessor.pickle', 'wb'))

    model = EllipticEnvelope()
    model.fit(np.asarray(data))

    pickle.dump(model, open('model.pickle', 'wb'))

    print('Finished Training! You can know predict outliers by calling the predict_norm.py ' +
        'or train a better model at a later time given more data')

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
