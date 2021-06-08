#! /bin/bash

echo "Viruses File is: $1"
echo "Countries File is: $2"
echo "Number of Lines is: $3"
echo "Number for Duplicates is: $4"
echo "Number of given parameters is: $#"

# check if testInputFile exist and remove it to create from beginning
if [ ! -f testInputFile ]
then
  echo "File does not exist. It will be created for the first time. Skipping..."
else
  rm testInputFile
  echo "File testInputFile exist. We delete it so it can be created from the beginning."
fi
# end of removing

# check if the number of parameters given is correct
if [ $# -ne 4 ]; then
	echo -e -n "\033[1;31m[Error]"
    echo -e "\033[0m You must enter exactly 4 command line arguments "
    exit 1
else 
    echo -e -n "\033[1;32m[Info]"
    echo -e "\033[0m Well done! You gave $# parameters. "
fi
# end of checking number of parameters

# check if the file name given in the 1st command line parameter exist and is readable
if [ -e $1 ]; then
    if [ -f $1 ]; then
        if [ -r $1 ]; then
            echo -e -n "\033[1;32m[Info]"
            echo -e "\033[0m $1 is a valid file."
        else 
            echo -e -n "\033[1;31m[Error]"
            echo -e "\033[0m $1 is not a readable file. "
            exit 1
        fi
    else 
        echo -e -n "\033[1;31m[Error]"
        echo -e "\033[0m $1 is not a file.  "
        exit 1
    fi
else 
    echo -e -n "\033[1;31m[Error]"
    echo -e "\033[0m $1 does not exist.  "
    exit 1    
fi
#end of checking 1st parameter

# check if the file name given in the 2nd command line parameter exist and is readable
if [ -e $2 ]; then
    if [ -f $2 ]; then
        if [ -r $2 ]; then
            echo -e -n "\033[1;32m[Info]"
            echo -e "\033[0m $2 is a valid file."
        else 
            echo -e -n "\033[1;31m[Error]"
            echo -e "\033[0m $2 is not a readable file. "
            exit 1
        fi
    else 
        echo -e -n "\033[1;31m[Error]"
        echo -e "\033[0m $2 is not a file.  "
        exit 1
    fi
else 
    echo -e -n "\033[1;31m[Error]"
    echo -e "\033[0m $2 does not exist.  "
    exit 1    
fi
#end of checking 2nd parameter

# check if the 3rd parameter is a positive number
if [ "$3" -le 0 ]; then
    echo -e -n "\033[1;31m[Error]"
    echo -e "\033[0m The numLines parameter must not be a negative number or zero. "
    exit 1
else 
    echo -e -n "\033[1;32m[Info]"
    echo -e "\033[0m The numLines parameter is the valid number: $3 "
fi
# end of checking 3rd parameter

# check if the 3rd parameter is a number
re='^[0-9]+$'
if ! [[ $3 =~ $re ]] ; then
	echo -e -n "\033[1;31m[Error]"
	echo -e "\033[0m You must enter a number at the 3rd command line argument" >&2; 
	exit 1
fi
# end of checking 3rd parameter

# check if the 4th parameter is a number greater than -1
if [ "$4" -le -1 ]; then
    echo -e -n "\033[1;31m[Error]"
    echo -e "\033[0m The numLines parameter must not be a negative number. "
    exit 1
else 
    echo -e -n "\033[1;32m[Info]"
    echo -e "\033[0m The numLines parameter is the valid number: $4 "
fi
# end of checking 4th parameter

# check if the 4th parameter is a number
re='^[0-9]+$'
if ! [[ $4 =~ $re ]] ; then
    echo -e -n "\033[1;31m[Error]"
    echo -e "\033[0m You must enter a number at the 4th command line argument" >&2; 
    exit 1
fi
# end of checking 4th parameter

# check if the 4th parameter is 0 or 1
# if !([ "$4" -eq 1 ] || [ "$4" -eq 0 ]); then
# 	echo -e -n "\033[1;31m[Error]"
#     echo -e "\033[0m You must enter 0 or 1 at the 4th command line argument" 
#     exit 1 
# else 
#     echo -e -n "\033[1;32m[Info]"
#     echo -e "\033[0m The duplicatesAllowed parameter is the valid number: $4 " 
# fi
# end of checking 4th parameter

# read viruses file line by line
echo "Content of viruses file:"
while read line; do
	echo $line
done < "$1"
# end of reading virus file 
echo ""
echo ""
# read countries file line by line
echo "Content of countries file:"
while read line; do
	echo $line
done < "$2"
# end of reading countries file 

# creating a new empty file  
touch testInputFile
echo -e -n "\033[1;32m[Info]"  
echo -e "\033[0m The new file has been created! " 
# end of creating the new empty file

# write records in the new file
viruses=( $(cat "$1") )
countries=( $(cat "$2") ) 
for (( i=1; i<=$3; i++ )); do

    # create citizenID from 1 to 9999
    rand=$(od -A n -t d -N 2 /dev/urandom |tr -d ' ')
    citizenID=$((rand % 9999 +1))
    #id=$((RANDOM % 10000))

    # create name with length 3 to 12
    rand=$(od -A n -t d -N 2 /dev/urandom |tr -d ' ')
    nameLength=$((rand % 9 +3))
    name=`head /dev/urandom | tr -dc A-Za-z0-9 | head -c $nameLength ; echo ''`

    # create surname with length 3 to 12
    rand=$(od -A n -t d -N 2 /dev/urandom |tr -d ' ')
    surnameLength=$((rand % 9 +3))
    surname=`head /dev/urandom | tr -dc A-Za-z0-9 | head -c $surnameLength ; echo ''`

    # create country name
    rand=$(od -A n -t d -N 2 /dev/urandom |tr -d ' ')
    c=$((rand % ${#countries[@]}))
    countryName=${countries[$c]}

    # create age
    rand=$(od -A n -t d -N 2 /dev/urandom |tr -d ' ')
    age=$((rand % 120 +1 ))

    # create virus name
    rand=$(od -A n -t d -N 2 /dev/urandom |tr -d ' ')
    v=$((rand % ${#viruses[@]}))
    virusName=${viruses[$v]}

    # create yes/no
    rand=$(od -A n -t d -N 2 /dev/urandom)
    yn=$((rand % 2))
    if [ $yn -eq 0 ]; then
        y_n="NO"
    else 
        y_n="YES"
    fi
    
    # create date
    if [ $yn -eq 1 ]; then
        date=`date -d "$((RANDOM%3+2016))-$((RANDOM%12+1))-$((RANDOM%28+1))" '+%d-%m-%Y'`
    else 
        date=""
    fi

    # write the new record in the file
    echo $citizenID $name $surname $countryName $age $virusName $y_n $date >> testInputFile 

    # if dublicates allowed and we haven't write all the records yet, 
    # random decide if the next record will have same id, name, surname, country and age 
    # but maybe a different virus, yes/no and date.
    rand=$(od -A n -t d -N 2 /dev/urandom)
    r=$((rand % 15))
    # if duplicates allowed
    if !([ "$4" -eq 0 ]); then
    	# and if random lets as duplicate
    	if [ $r -eq 1 ]; then
    		# and if we haven't write the last record
    		if !([ $i -eq $3 ]); then

	    		# create virus name
			    rand=$(od -A n -t d -N 2 /dev/urandom |tr -d ' ')
			    v=$((rand % ${#viruses[@]}))
			    virusName=${viruses[$v]}

			    # create yes/no
			    rand=$(od -A n -t d -N 2 /dev/urandom)
			    yn=$((rand % 2))
			    if [ $yn -eq 0 ]; then
			        y_n="NO"
			    else 
			        y_n="YES"
			    fi
			    
			    # create date
			    if [ $yn -eq 1 ]; then
			        date=`date -d "$((RANDOM%3+2016))-$((RANDOM%12+1))-$((RANDOM%28+1))" '+%d-%m-%Y'`
			    else 
			        date=""
			    fi

	    		echo $citizenID $name $surname $countryName $age $virusName $y_n $date >> testInputFile
	    		i=$((i+1))
	    	fi
    	fi
    fi

done
# end of writing in the new file

#read a random line from virus file
# shuf -n 1 "$fileName1"
#end of reading a random line