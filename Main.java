import java.util.Scanner;

public class Main {

    static{
        System.loadLibrary("ntfsutils");
    }

    public static void main(String[] args) {

        Main main = new Main();

        if (args.length >= 1 && args[0].equals("list")){
            main.print_devices();
            return;
        }

        if (args.length >= 2 && args[0].equals("shell")){

            int init = main.initFS(args[1]);
            if (init == -1){
                System.out.println("filesystem is not NTFS");
                return;
            } else {
                System.out.println("NTFS filesystem detected");
            }

            Scanner scanner = new Scanner(System.in);
            boolean exit = false;
            String pwd;
            String[] input;
            String output;
            while (!exit){
                pwd = main.pwd();
                System.out.print(pwd + "> ");
                input = scanner.nextLine().split(" ");
                switch (input[0]) {
                    case "exit":
                        exit = true;
                        break;
                    case "help":
                        System.out.println("cd [directory] - change working directory");
                        System.out.println("pwd - print working directory full name");
                        System.out.println("cp - [directory] [target directory] - copy dir or file from mounted device");
                        System.out.println("ls - show working directory elements");
                        System.out.println("exit - terminate program");
                        System.out.println("help - print help   ");
                        break;
                    case "ls":
                        String path = input.length >= 2 ? input[1] : ".";
                        output = main.ls(path);
                        System.out.print(output);
                        break;
                    case "pwd":
                        output = main.pwd();
                        System.out.print(output);
                        break;
                    case "cd":
                        if (input.length >= 2){
                            output = main.cd(input[1]);
                            System.out.print(output);
                        } else {
                            System.out.println("cd command require path argument");
                        }
                        break;
                    case "cp":
                        switch (input.length){
                            case 3:
                                output = main.cp(input[1], input[2]);
                                System.out.print(output);
                                break;
                            case 2:
                                System.out.println("cp command require \"out_path\" argument");
                                break;
                            default:
                                System.out.println("cp command require \"path\" and \"out_path\" arguments");
                                break;
                        }
                        break;
                    default:
                        System.out.println("wrong command. Enter 'help' to get help");
                }
            }
            main.closeFS();
            return;
        }

        System.out.println("incorrect command line arguments. Run with 'help' argument to get help");
    }

    private native void print_devices();
    private native String ls(String path);
    private native String cd(String path);
    private native String pwd();
    private native String cp(String path, String outPath);
    private native int initFS(String path);
    private native void closeFS();
}
