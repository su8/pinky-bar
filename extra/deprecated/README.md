The bash bootstrip script served well until I ported pinky-bar to \*BSD, as I had to make bash as dependency.

Second attemp was with GNU make and sed, and the difference between GNU and BSD sed version made me to pull out my hair. So I re-wrote the sed macros to use perl instead.

The third and last attemp - deprecate GNU make, and use only perl. Since it high-level language it will be portable across different operating systems, and the bonus is that perl will be most likely installed out of the box.
