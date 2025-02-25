; ModuleID = 'print_functions'
source_filename = "print_functions.c"

@.str_nl = private unnamed_addr constant [3 x i8] c"%s\00", align 1
@.str_ln = private unnamed_addr constant [4 x i8] c"%s\0A\00", align 1

declare i32 @printf(i8*, ...) #1

define void @print(i8* %str) #0 {
entry:
  %call = call i32 (i8*, ...) @printf(i8* getelementptr ([3 x i8], [3 x i8]* @.str_nl, i32 0, i32 0), i8* %str)
  ret void
}

define void @println(i8* %str) #0 {
entry:
  %call = call i32 (i8*, ...) @printf(i8* getelementptr ([4 x i8], [4 x i8]* @.str_ln, i32 0, i32 0), i8* %str)
  ret void
}

attributes #0 = { nounwind }
attributes #1 = { "builtin" }
