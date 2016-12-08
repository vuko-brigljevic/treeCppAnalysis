import argparse

import ROOT
import os
import subprocess

def inplace_change(filename, old_string, new_string):
    # Safely read the input filename using 'with'
    with open(filename) as f:
        s = f.read()
        if old_string not in s:
            print '"{old_string}" not found in {filename}.'.format(**locals())
            return
        
    # Safely write the changed content, if found in the file
    with open(filename, 'w') as f:
        print 'Changing "{old_string}" to "{new_string}" in {filename}'.format(**locals())
        s = s.replace(old_string, new_string)
        f.write(s)

def make_directory(directory):

    if not os.path.isdir(directory):
        try:
            os.makedirs(directory)
        except OSError:
            if not os.path.isdir(directory):
                raise


#------------------------------------------------------------------------- 
#  PARSE COMMAND LINE ARGUMENT
#-------------------------------------------------------------------------

parser = argparse.ArgumentParser(description='Run v0Analyser')

parser.add_argument('-i', action="store", dest = 'infile')
#                    default="l_pp40_AntoniEvCuts_noWFA_gtpc.root")
parser.add_argument('-t', action="store", dest = 'treeName', default ='')
parser.add_argument('-c', action="store", dest = 'TreeClass', default = 'EventClass')
parser.add_argument('-e', action="store", dest = 'EventClass', default = 'Event')
parser.add_argument('-m', action="store", dest = 'analyzer', default = 'Analyzer')
parser.add_argument('-d', action="store", dest = 'workdir', default = 'workdir')
parser.add_argument('-a', action="store", dest = 'analysisClass', default = 'UserAnalysis')



parsed_args = parser.parse_args()

#


exampleRootFile = "file.root"
exampleTree     = "tree"

className  = "EventClass"
EventClass = "HbbEvent"


analyzer = "HbbAnalyzer"



make_directory(parsed_args.workdir)


#templateDir="/users/vuko/phan/templateCppAnalysis/"
templateDir=os.getcwd()

os.chdir(parsed_args.workdir)


#
# Make the tree class with MakeClass in ROOT
#

_input_file = ROOT.TFile.Open( parsed_args.infile, 'read')
_tree       = _input_file.Get(parsed_args.treeName)
_tree.MakeClass(parsed_args.TreeClass)


# Now copy all files

commands = [ 
    "cp " + templateDir + "/TreeEvent.h " + parsed_args.workdir + "/" + parsed_args.EventClass + ".h",
    "cp " + templateDir + "/TreeEvent.C " + parsed_args.workdir + "/" + parsed_args.EventClass + ".C",
    "cp " + templateDir + "/TreeAnalysis.h " + parsed_args.workdir + "/" + parsed_args.analysisClass + ".h",
    "cp " + templateDir + "/TreeAnalysis.C " + parsed_args.workdir + "/" + parsed_args.analysisClass + ".C",
    "cp " + templateDir + "/analyzeTree.cpp " + parsed_args.workdir + "/" + parsed_args.analyzer + ".cpp",
    "cp " + templateDir + "/Makefile " + parsed_args.workdir + "/" 
    ]

for com in commands:
    subprocess.call(com, shell=True)  


namesToSwitch = {
    "TreeClass" : parsed_args.TreeClass ,
    "TreeEvent" : parsed_args.EventClass, 
    "TREE_IN_ROOTFILE" : parsed_args.treeName,
    "analyzeTree"      : parsed_args.analyzer,
    "TreeAnalysis"     : parsed_args.analysisClass
    }

filesToProcess = [
    parsed_args.EventClass+".h",
    parsed_args.EventClass+".C",
    parsed_args.analysisClass+".h",
    parsed_args.analysisClass+".C",
    "Makefile",
    parsed_args.analyzer+".cpp"
]

for key in namesToSwitch:
    for file in filesToProcess:
        file_full_path = parsed_args.workdir + "/" + file
        inplace_change(file_full_path , key , namesToSwitch[key])



#
#open("x.txt") as f:
#   data = f.read()
#   do something with data





