## Exercise 2

Let $\mathcal{I} := \left\{\{A^{(i)}\}_{i\in N} : N\subseteq \{1,\dots, k\cdot n\} \text{ and } \{A^{(i)}\} \text{ are linearly independent}\right\}$ where $A\in\mathbb{R}^ {n\times k\cdot n}$ and $A^{(i)}$ denotes the $i$-th column. Then, with $E:= \{A^{(i)}\}_{i\in\{1,\dots, k\cdot n\}}$, we see that $\mathcal{M} := (E,\mathcal{I})$ is a matroid.

1. Given $\{A^{(i)}\}_{i\in N}\in\mathcal{I}$, if we get rid of any column $k\in N$, $\{A^{(i)}\}_{i\in N\setminus \{k\}}$ are still linearly independent
2. Given $X:=\{A^{(i)}\}_{i\in N}$,$Y:=\{A^{(i)}\}_{i\in M}$, they're both in $\mathcal{I}$ by definition. If $|M| > |N|$, then $Y\setminus X$ contains at least one element which is linearly independent with the elements in $X$, since if it didn't, we could write the elements of $Y$ as vectors in $\mathbb{R}^|N|$, according to the coordinates they get in base $X$, and find a way to express a vector of $Y$ as a linear combination of the rest, contradicting the fact that the elements in $Y$ are linearly independent. Therefore, $\exists k\in N$ such that $X\cup\{A^{(k)}\}\in\mathcal{I}$.

