import os

def move_file(root, dirs, files):
    
    for f in files:
        obj_f = os.path.join(root, f)
        new_p = os.path.join(content_dir, f)
        os.rename(obj_f, new_p)
        print(obj_f, new_p, "\n")
        


content_dir = "."
for root, dirs, files in os.walk("."):
    if len(files)==0:
        continue
    if root.split(r'/')[-1] == "img":
        os.rename(root, r"./img")
        print(root, r"./img", "\n")

    move_file(root, dirs, files)

