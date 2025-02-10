from cryptography.fernet import Fernet
import os
#encryption_key = Fernet.generate_key()

def main():
    
    global d,f,password,username
    #Userername = '$laksh07'
    #Password = '$Laksh2106'
    os.system('cls')
    with open('database.txt', 'r') as db:
        username = input("Username: ")
        password = input("Password: ")
        d = []
        f = []
        for ii in db:
            a,b = ii.split(", ")
            b = b.strip()
            
            d.append(a)
            f.append(b)
        data = zip(d, f)
        
        if  username in d:
            n = d.index(username)
        
            if password == f[n]:
                #print(d[n],f[n])
                print("LOGIN SUCCESS!!!")
                Logafter()
            else:
                print("!!!INVALID PASSWORD!!!\n")
        else:
            print("INVALID CREDENTIALS...\n")
            exit

def Logafter():
    encryption_key = b'g5rpWlh1X0cs27Uh9jf5Hs_GMUn5bPp-b_QfB_3h0jg='    #VERY IMPORTANT
    cipher_suite = Fernet(encryption_key)                               #VERY IMPORTANT
    print("\n\n1.ENCRYPT  2.DECRYPT  3.forgot password?  4.EXIT  5.FILE")
    i = -1
    while i < 0:
        choice = int(input("\nENTER CHOICE: "))
        if choice == 1:
            c = input("Enter message: ")
            b = bytes(c, "utf-8")
            encrypted_value = cipher_suite.encrypt(b)
            enc = encrypted_value.decode()   
            print("Encrypted value: ",enc)

        elif choice == 2:
            decrypted_value = input("Enter encrypted message: ")
            decrypted_value = cipher_suite.decrypt(decrypted_value)
            dec = decrypted_value.decode()
            print("Decrypted value: ",dec)
            
        
        elif choice == 3:
            Cuser = input("\nPlease Enter your current Username: ")
            if Cuser in d:
                n = d.index(Cuser)
                Cpass0 = input("Enter password: ")
                Cpass = input("Re-enter password: ")
                if Cpass0 == Cpass:
                    with open('database.txt', 'r') as db:
                        dat = db.read()
                        dat = dat.replace(password, Cpass)

                    with open('database.txt', 'w') as db:
                        db.write(dat)
                                                
                    print("PASSWORD successfully changed")

        elif choice == 4:
            print("THANK YOU!!!\n")
            i = 0
            pass

        elif choice == 5:
            os.system('cls')
            encdec = input("Do you want to encrypt or decrypt, enc or dec: ")
            if encdec == 'enc':
                encryption_key = b'g5rpWlh1X0cs27Uh9jf5Hs_GMUn5bPp-b_QfB_3h0jg='    #VERY IMPORTANT
                cipher_suite = Fernet(encryption_key)
                fname1 = input("Enter file name you want to encrypt: ")
                fname2 = input("How do you want to save encrypted message as: ")

                with open(fname1, 'r') as file1:
                    file2 = open(fname2,'w')
                    for line in file1:
                        encryption_key = b'g5rpWlh1X0cs27Uh9jf5Hs_GMUn5bPp-b_QfB_3h0jg='    #VERY IMPORTANT
                        cipher_suite = Fernet(encryption_key)
                        c = line
                        b = bytes(c, "utf-8")
                        encrypted_value = cipher_suite.encrypt(b)
                        enc = encrypted_value.decode()   
                        #print("Encrypted value: ",enc)
                        file2.write(enc)
                    
                        #file2.write(line)
                    file2.close()

            if encdec == 'dec':
                
                fname1 = input("Enter file name you want to decrypt: ")
                dec_info = input("Do you want to save the decrypted message(y/n): ")
                fd1 = open(fname1,'rb')
                if dec_info == 'n':
                    msg = fd1.read()
                    decrypted_value = msg
                    decrypted_value = cipher_suite.decrypt(decrypted_value)
                    dec = decrypted_value.decode()
                    print("Decrypted value: ",dec)
                
             
                fd1.close()
                

        else:
            print("INVALID CHOICE")

main()

#FILE DECRYPTION NOT WORKING, ENCRYPTION WORKS!