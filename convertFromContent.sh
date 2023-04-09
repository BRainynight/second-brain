rm -rf content/notes
cp -r /d/Database/PKM content/notes
rm -rf content/notes/private
rm -rf content/notes/template
hugo-obsidian -input=content -output=assets/indices -index -root=.
