while true; do 
	clear
	g++ Exercise3.cpp -g -o program.out \
		&& echo -e "\e[32mBegining of output\e[m" \
		&& ./program.out < Exercise3.args \
		&& echo -e "\e[32mEnd of output (Enter to copy, Ctrl+D to debug, Ctrl+C to exit):\e[m" \
		&& read q && xclip -sel clip < Exercise3.cpp \
		|| gdb -q --ex "b KruskalsDual" --ex "r < Exercise3.args" program.out
done

