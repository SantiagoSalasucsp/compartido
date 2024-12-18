import sysv_ipc
import time
import sys

KEY = 0x1111      
SHM_KEY = 5678    
SHM_SIZE = 27   

def px_python(text, V):
    try:
        
        semaphore = sysv_ipc.Semaphore(KEY)

       
        shared_memory = sysv_ipc.SharedMemory(SHM_KEY,flags=sysv_ipc.IPC_CREAT,mode=0o666,size=27)

        while True:
           
            semaphore.acquire()

            
            shmv = int(shared_memory.read(3).decode('utf-8'))

            if shmv == (V - 1):
                # escribir en shm 
                text_final = f"{V:03d}"+text+'\0'
                v_bytes = text_final.encode('utf-8')
                shared_memory.write(v_bytes)
                
                V += 4

           
            semaphore.release()
            time.sleep(1)

    except sysv_ipc.ExistentialError as e:
        print(f"Error accessing shared memory or semaphore: {e}")
    except Exception as e:
        print(f"Unexpected error: {e}")
    finally:
        shared_memory.detach()

if __name__ == "__main__":
    if len(sys.argv) != 3:
        print("Usage: python3 px_python.py <text> <number>")
    else:
        px_python(sys.argv[1], int(sys.argv[2]))
