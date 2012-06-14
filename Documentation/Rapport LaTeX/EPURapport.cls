%% $Id: EPURapport.cls 31 2009-04-24 08:26:06Z 20404185t $

\NeedsTeXFormat{LaTeX2e}

%----- Identification -----
\ProvidesClass{EPURapport}[2009/04/24 - EPURapport document class]

%----- Required Packages -----
\RequirePackage{lmodern} %% A nice font
\RequirePackage[T1]{fontenc}
\RequirePackage{ifthen}
\RequirePackage{fancyhdr} %% Bling-bling headers and footers

%----- Options -----
\newboolean{BTwoPages}
\newboolean{BFourPages}
\newboolean{BUTF8}
\newboolean{BFinal}

\DeclareOption{UTF8}{
	\setboolean{BUTF8}{true}
}

\DeclareOption{twoside}{
	\PassOptionsToClass{twoside}{report}
	\setboolean{BTwoPages}{true}
}
\DeclareOption{fourside}{
	\PassOptionsToClass{twoside}{report}
	\setboolean{BTwoPages}{true}
	\setboolean{BFourPages}{true}
}

\DeclareOption*{\PassOptionsToClass{\CurrentOption}{report}}

\DeclareOption{final}{
	\PassOptionsToClass{\CurrentOption}{final}
	\setboolean{BFinal}{true}
}

%----- Execution of Options -----
\ProcessOptions

\ifthenelse{\boolean{BUTF8}}{\RequirePackage[utf8]{inputenc}}{}

%----- Initial Class -----
\LoadClass[11pt,a4paper]{report}
\RequirePackage[francais]{babel}
\RequirePackage{url}
\RequirePackage{xcolor}
\RequirePackage{comment}
\RequirePackage{lastpage}
\RequirePackage{fp} %% Arithmetic functions
\RequirePackage{graphicx}
\RequirePackage{hyperref} %% Clicka-proof links

%----- Dimensions -----
\setlength{\evensidemargin}{2cm}
\setlength{\oddsidemargin}{2cm}
\setlength{\textheight}{\paperheight}
\addtolength{\textheight}{-5.7cm} % 24cm
\setlength{\textwidth}{\paperwidth}
\addtolength{\textwidth}{-4cm} % 17cm
\setlength{\topmargin}{0.5cm}
\setlength{\headheight}{2cm}
\setlength{\headsep}{0.5cm}
\setlength{\voffset}{-2.54cm}
\setlength{\hoffset}{-2.54cm}
\setlength{\footskip}{1.5cm}

%----- Personnal config -----
\def\notableofcontents{%
	\renewcommand{\tableofcontents}{}
}

\def\nolistoffigures{%
	\renewcommand{\listoffigures}{}
}

\def\nolistoftables{%
	\renewcommand{\listoftables}{}
}

\newcommand{\addextratables}[1]{%
	\def\extratables{#1}
}

\def\nosupervisors{%
	\renewcommand{\supervirorsDisplay}{}
}

%----- HyperRef configuration -----
\hypersetup{
	colorlinks=true,
	urlcolor=blue,
	breaklinks=true,
	bookmarksopen=true,
	bookmarksnumbered=true,
	plainpages=false,
	pdfdisplaydoctitle=true,
	hypertexnames=false, %% Suppress lots of warnings
	citecolor=blue,
	linkcolor=black %% Internal links (TOC, ...)
}

%----- Urls -----
\urlstyle{sf}

\newcommand{\email}[1]{
	\href{mailto:#1}{#1}
}

%----- Getting informations -----
%%%--- Document ---
\newcommand{\thedocument}[3]{%
	\def\thedocumenttype{#1}% Rapport de projet, Rapport de stage de fin d'ann\'ee, Rapport de stage de fin d'\'etudes...
	\def\thedocumentlongtitle{#2}
	\def\thedocumentshorttitle{#3}
	
	%% Title and subject in pdf properties
	\hypersetup{
		pdftitle={\thedocumentlongtitle{}}
	}
}

%%%--- Grade ---
%(Parcours des \'Ecoles d'Ing\'enieur Polytech, 1\iere{} ann\'e, D\'epartement Informatique, 2\ieme{} ann\'e...)
\newcommand{\grade}[1]{%
	\def\theLongGrade{#1}
}

%%%--- Entity ---
\newcommand{\entitylogo}[1]{%
	\def\theentitylogo{#1}
}

%%%--- Authors & Supervisors ---

%--- We will use functors...
%--- Short version of name and mail
\newcommand{\shortname}[1]{#1}
\newcommand{\shortmail}[1]{<#1>}
\newcommand{\shortcategory}[2]{#2}
\newcommand{\shortdetails}[1]{}
%--- Long version of name and mail
\newcommand{\longname}[1]{#1\\}
\newcommand{\longmail}[1]{\email{#1}\\}
\newcommand{\longcategory}[2]{
	\textbf{#1}

	#2~\\
}
\newcommand{\longdetails}[1]{#1\\}

\newcommand{\authors}[1]{%
	\def\listauthors{#1}
	
	% That is functors !!!
	\def\name{\shortname}
	\def\mail{\shortmail}
	\def\category{\shortcategory}
	\def\details{\shortdetails}
	
	\hypersetup{
		pdfauthor={\listauthors}
	}
}

\newcommand{\supervisors}[1]{%
	\def\listsupervirors{#1}
}

%%%--- Abstracts and Keywords ---
\newcommand{\abstracts}[4]{%
	\def\thefrenchabstract{#1}
	\def\thefrenchkeywords{#2}
	\def\theenglishabstract{#3}
	\def\theenglishkeywords{#4}
	
	%%French Keywords in document properties
	\hypersetup{
		pdfsubject={\thefrenchabstract{}},
		pdfkeywords={\thefrenchkeywords{}}
	}
}

%----- Displaying authors and supervirors -----

\newcommand{\authorsDisplay}{
	\def\name{\longname}
	\def\mail{\longmail}
	\def\category{\longcategory}
	\def\details{\longdetails}
	\listauthors{}
}

\newcommand{\supervirorsDisplay}{
	\def\name{\longname}
	\def\mail{\longmail}
	\def\category{\longcategory}
	\def\details{\longdetails}
	\listsupervirors{}
}

\newcommand{\authorsAndSupervisorsDisplay}{%
	\noindent\begin{minipage}[t]{8cm}
		\begin{flushleft}
			\ifthenelse{ \isundefined{\swapAS} }{\supervirorsDisplay{}}{\authorsDisplay{}}
		\end{flushleft}
	\end{minipage}
	\hfill
	\begin{minipage}[t]{8cm}
		\begin{flushright}
			\ifthenelse{ \isundefined{\swapAS} }{\authorsDisplay{}}{\supervirorsDisplay{}}
		\end{flushright}
	\end{minipage}
}

\newcommand{\swapAuthorsAndSupervisors}{
	\def\swapAS{}
}

\newcommand{\annexes}{
	\appendix
	\renewcommand\chaptername{\appendixname}
}

\def\schoolLogo{logos/Logo_Polytech_Tours}

%----- First Page -----
\newcommand{\thefirstpage}{%
\thispagestyle{empty}
	\sffamily
	%\setcounter{page}{1}
	\begin{center}
		\includegraphics[width=8cm]{\schoolLogo}

		\bigskip	

		{
			{\'Ecole Polytechnique de l'Universit\'e de Tours}\\
			64, Avenue Jean Portalis\\
			37200 TOURS, FRANCE\\
			T\'el. +33 (0)2 47 36 14 14\\
			%Fax  +33 (0)2 47 36 14 22\\
			\href{http://www.polytech.univ-tours.fr}{\texttt{www.polytech.univ-tours.fr}}
		}

		\bigskip

		{\LARGE \textbf{\theLongGrade}

		\vfill

		\textbf{\thedocumenttype}}
		
		\ifthenelse{ \isundefined{\theentitylogo} } % si l'on a un logo defini
		{}{\bigskip \includegraphics[height=2cm]{\theentitylogo}}

		\vfill
		
		{\Huge \textbf{\thedocumentlongtitle}}
		
		\vfill
	
		\authorsAndSupervisorsDisplay
		
		\ifthenelse{\boolean{BFinal}}{}{~\newline {\small Version du \today}}

	\end{center}
	
	\ifthenelse{\boolean{BTwoPages}}%
	{% On commence sur une page droite
		\newpage~\thispagestyle{empty}\newpage
	}{}
	
	% Affichage des pages en chiffres romains pour les pages informatives
	\renewcommand{\thepage}{\Roman{page}}
	
	% Affichage des tables et listes habituelles
	\tableofcontents
	\listoffigures
	\listoftables
	% Et des non habituelles
	\ifthenelse{\isundefined{\extratables}}
	{}{\extratables}
	\newpage
	
	
	% Affichage des numeros de pages en chiffres arabes pour le corps du document
	\renewcommand{\thepage}{\arabic{page}}
	% Liens internes de nouveau en rouge
	\hypersetup{linkcolor=red}
}

%----- Last Page -----
\newcommand{\thelastpage}{%
	% Si on est en mode twosides, on va chercher a avoir un
	% nombre de pages multiple de 4
	\ifthenelse{\boolean{BTwoPages}}
	{%
		\ifthenelse{\boolean{BFourPages}}{ \FPset{\DivB}{4} }{ \FPset{\DivB}{2} }
	
		\FPset{\DivA}{\thepage}
	
		%% Decomposition du nb de pages en A = BQ+R
		%% Compiler avec --shell-escape pour avoir le debug
		%% C'est le R qui nous interesse
		%%% Example : DivA = 26 pages
		%\immediate\write18{printf "Nombre de pages : \DivA"}
	
		\FPdiv{\tmpDivQ}{\DivA}{\DivB} %% /4 ou /2
		%\immediate\write18{printf "Division : \tmpDivQ"}
		%%% tmpDivQ = 6.75
	
		\FPtrunc{\DivQ}{\tmpDivQ}{0} %% Nb de paquets complets de 4 pages
		%\immediate\write18{printf "Nombre de paquets de 4 pages : \DivQ"}
		%%% DivQ = 6
	
		\FPmul{\DivBQ}{\DivQ}{\DivB}
		%\immediate\write18{printf "Nombre de pages en paquet : \DivBQ"}
		%%% DivBQ = 24
	
		\FPsub{\DivR}{\DivA}{\DivBQ}
		\FPtrunc{\DivR}{\DivR}{0}
		%\immediate\write18{printf "Nombre de pages hors paquet : \DivR"}
		%%% DivR = 27-24 = 3
	
		\FPifzero{\DivR}
		{
			\FPset{\DivB}{0}
			%\immediate\write18{printf "On ne rajoutera pas de pages : \DivR, \DivB"}
		}\else {
			%\immediate\write18{printf "On rajoutera des pages"}
		}
	
		\FPsub{\Delta}{\DivB}{\DivR}
		\FPtrunc{\Delta}{\Delta}{0}
		%\immediate\write18{printf "Nombre de pages a ajouter : \Delta"}
		%%% Delta = 4-3 = 1
	
		\loop
			\FPsub{\Delta}{\Delta}{1}
			\FPifpos{\Delta}{
				%\immediate\write18{printf "Ajout d'une page \Delta"}
				\newpage~\thispagestyle{empty}
			}
		\repeat
	}{}
	
	% En mode "twoside", la derniere page sera impaire, il faut donc 
	% intercepter l'ajout d'une page supplementaire.
	\renewcommand\clearemptydoublepage{}
	\chapter*{\thedocumentlongtitle}
	\thispagestyle{empty}
	\vspace{-1cm}
	\begin{center}
		{\large\theLongGrade}\\~\\
		{\large\thedocumenttype}\\~\\
	\end{center}

	\paragraph*{R\'esum\'e :} \thefrenchabstract
	\paragraph*{Mots clefs :} \thefrenchkeywords
	\paragraph*{Abstract:} \theenglishabstract
	\paragraph*{Keywords:} \theenglishkeywords
	\vspace{1cm}
	\hrule
	\vfill
	
	\authorsAndSupervisorsDisplay
}

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% 
%----- Header/footer Format -----
\pagestyle{fancy}

% Affichage du titre du chapitre
%% \chaptername = "Chapitre"
%% \thechapter = numero du chapitre
%% #1 = nom du chapitre
%% --> leftmark
\renewcommand{\chaptermark}[1]{%
	\markboth{\chaptername\ \thechapter. \ #1}{}
}

% Affichage du titre de la section
%% #1 = nom de la section
%% --> rightmark
\renewcommand{\sectionmark}[1]{\markright{#1}}

% Largeur de l'en-tete
% On enleve 4cm afin de pouvoir placer lo logo
\newlength{\headersize}
\setlength{\headersize}{\textwidth}
\addtolength{\headersize}{-4cm}

% Logo utilise dans l'en-tete
\newsavebox{\EPUlogo}
\sbox{\EPUlogo}{\includegraphics[width=2.6cm]{\schoolLogo}}

\ifthenelse{\boolean{BTwoPages}}{% Twosides mode
	
	\fancyhead[LE]{% En-tete, champ gauche, page paire (gauche)
		\begin{minipage}[c]{3cm}\usebox{\EPUlogo}\end{minipage}%
		\begin{minipage}{\headersize}%
		{%
			\bfseries\leftmark%
		}%
		\end{minipage}%
	}
	
	\fancyhead[RO]{% En-tete, champ droit, page impaire (droite)
		\begin{minipage}{\headersize}%
		{%
			\begin{flushright}\bfseries\rightmark\end{flushright}%
		}%
		\end{minipage}%
		\begin{minipage}[c]{3cm}\hfill\usebox{\EPUlogo}\end{minipage}%
	}
	
	% En tete, champ droit page paire (gauche), et champ gauche page impaire (droite) 
	\fancyhead[RE,LO]{}
	
	% Pied de page
	\fancyfoot[LE,RO]{\bfseries\thepage}
	\fancyfoot[RE,LO]{\bfseries\thedocumentshorttitle}
	%% Pour les pages avec titre
	\fancypagestyle{plain}{%
		\fancyfoot[LE,RO]{\bfseries\thepage}
		\fancyfoot[RE,LO]{}
	}
}{% Oneside mode
	% En-tete, champ gauche
	\fancyhead[L]{%
		\begin{minipage}{3cm}\usebox{\EPUlogo}\end{minipage}%
		\begin{minipage}{\headersize}%
		{%
			\bfseries\leftmark\\%
			\rightmark%
		}%
		\end{minipage}%
	}
	
	% En-tete, champ gauche
	\fancyhead[R]{}
	
	% Pied de page
	\fancyfoot[R]{\bfseries\thepage}
	\fancyfoot[L]{\bfseries\thedocumentshorttitle}
	%% Page avec titre
	\fancypagestyle{plain}{%
		\fancyfoot[R]{\bfseries\thepage}
		\fancyfoot[L]{}
	}
}

%% Reglages valables dans tous les cas
% Rien au centre du pied de page
\fancyfoot[C]{}

% Epaisseur des lignes de separation
\renewcommand{\headrulewidth}{0pt}
\renewcommand{\footrulewidth}{0.2pt}

% Pages avec en-tete (debut de chapitre, table des matieres...)
\fancypagestyle{plain}{%
	\fancyhead{}% Rien dans l'en-tete
}

% Definit une ligne horizontale de 2px d'epaisseur
% sur 3/4 de la page. Utilisee pour souligner le 
% titre d'un chapitre.
\newcommand{\semirule}{\hbox to \hsize{\hfill
    \vrule height 2pt width.75\hsize
    \hfill}}

% Redifinition de l'en-tete d'un chapitre genere
% par la commande \chapter{}.
\def\@makechapterhead#1{%
  \begingroup
  \fontsize{\@xivpt}{18}\bfseries\centering
    \ifnum\c@secnumdepth>\m@ne
      \leavevmode \hskip-\leftskip
      \rlap{\vbox to\z@{\vss
	  \vskip 3pc}
	}\hskip\leftskip\fi
     \Huge\textsf{#1}\par\semirule\vspace{1cm} \endgroup
  \skip@34\p@ \advance\skip@-\normalbaselineskip
  \vskip\skip@ }

% Redifinition de l'en-tete d'un chapitre genere
% par la commande \chapter*{}. 
\def\@makeschapterhead#1{%
  \begingroup
  \fontsize{\@xivpt}{18}\bfseries\centering
  \Huge\textsf{#1}\par\semirule\vspace{1cm} \endgroup
  \skip@34\p@ \advance\skip@-\normalbaselineskip
  \vskip\skip@ }

% Fork de l'option cleardoublepage pour l'option "twoside". Permet
% d'ajouter une page avec un \thispagestyle "empty" au lieu de "plain"
\newcommand\clearemptydoublepage{\clearpage\if@twoside \ifodd\c@page\else
    \hbox{}\thispagestyle{empty}\newpage\if@twocolumn\hbox{}\thispagestyle{empty}\newpage\fi\fi\fi}

% Redefinition de la commande \chapter. Si on est en mode "twoside", 
% La page ajoutee afin de commencer un chapitre a droite sera empty
% et non "plain".
\renewcommand\chapter{\if@openright\clearemptydoublepage\else\clearpage\fi
                    \thispagestyle{plain}%
                    \global\@topnum\z@
                    \@afterindentfalse
                    \secdef\@chapter\@schapter}

% Gestion de la premiere et derniere page.
\AtBeginDocument{\thefirstpage}
\AtEndDocument{\thelastpage}
