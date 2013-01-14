SUBDIRS = test1

dist-hook: ChangeLog 

ChangeLog: configure.ac
    git log --stat --name-only --date=short --abbrev-commit  . > ChangeLog 

README: README.md
	ln -s $< $@

