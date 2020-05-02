package pack;
import java.util.*;
public class Main
{
    public static void main(String args[])
    {
       SLL s = new SLL();
       int ch;
       int x;
       Scanner input = new Scanner(System.in);
       do{
			System.out.print("Enter the data : ");
			x = input.nextInt();
			s.insert(x);
			
			System.out.print("Do want to add one more ?(1/0)");
			ch = input.nextInt();
		}while(ch == 1);
		
		s.display();
		System.out.print("Enter the data to delete : ");
		x = input.nextInt();
		s.delete(x);
		System.out.print("SLL after deletion :");
		s.display();
    }
}
 class node
{
    int data;
    node next;
    public node(int x)
    {
        this.data=x;
        this.next=null;
    }
}


 interface List{
     void insert(int x);
     void delete(int x);
     boolean search(int x);
     boolean empty();
}

 class SLL implements List
{
   node head;
   public SLL(){ head = null;}

   @Override
   public void insert(int x)
   {
       node temp= new node(x);
       if(head==null)
         head=temp;
        else
        {
           node p=head;
           while(p.next!=null)
           {
               p=p.next;
           }
           p.next = temp;
        }
   }
   @Override
	public void delete(int x) {
		// TODO Auto-generated method stub
		node t = head;
		if(t.data == x)
		{
			head = head.next;
		}
		else{
			while(t.next.data != x)
			{
				t=t.next;
			}
			t.next = t.next.next;
		}
	}

	public void display() {
		// TODO Auto-generated method stub
		node t = head;
		while(t != null)
		{
			System.out.print(t.data + "  ");
			t=t.next;
		}
	}

	@Override
	public boolean search(int x) {
		// TODO Auto-generated method stub
        node p=head;
        while(p!=null && p.data!=x)
        {
           p=p.next;
        }
		return p==null;
	}

	@Override
	public boolean empty() {
		// TODO Auto-generated method stub
		return head==null;
	}
}
