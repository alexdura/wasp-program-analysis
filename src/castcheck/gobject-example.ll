; ModuleID = 'gobject-example.c'
source_filename = "gobject-example.c"
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

%struct._GTypeInstance = type { %struct._GTypeClass* }
%struct._GTypeClass = type { i64 }
%struct.MyDogClass = type { %struct._GObjectClass }
%struct._GObjectClass = type { %struct._GTypeClass, %struct._GSList*, %struct._GObject* (i64, i32, %struct._GObjectConstructParam*)*, void (%struct._GObject*, i32, %struct._GValue*, %struct._GParamSpec*)*, void (%struct._GObject*, i32, %struct._GValue*, %struct._GParamSpec*)*, void (%struct._GObject*)*, void (%struct._GObject*)*, void (%struct._GObject*, i32, %struct._GParamSpec**)*, void (%struct._GObject*, %struct._GParamSpec*)*, void (%struct._GObject*)*, i64, [6 x i8*] }
%struct._GSList = type { i8*, %struct._GSList* }
%struct._GObject = type { %struct._GTypeInstance, i32, %struct._GData* }
%struct._GData = type opaque
%struct._GObjectConstructParam = type { %struct._GParamSpec*, %struct._GValue* }
%struct._GParamSpec = type { %struct._GTypeInstance, i8*, i32, i64, i64, i8*, i8*, %struct._GData*, i32, i32 }
%struct._GValue = type { i64, [2 x %union.anon] }
%union.anon = type { i64 }
%struct._MyDog = type { %struct._GObject, i32 }

@my_dog_get_type.g_define_type_id__volatile = internal global i64 0, align 8
@.str = private unnamed_addr constant [6 x i8] c"MyDog\00", align 1
@.str.1 = private unnamed_addr constant [5 x i8] c"WAF!\00", align 1
@my_dog_parent_class = internal global i8* null, align 8
@MyDog_private_offset = internal global i32 0, align 4
@.str.2 = private unnamed_addr constant [23 x i8] c"Initialized dog class\0A\00", align 1
@.str.3 = private unnamed_addr constant [17 x i8] c"Initialized dog\0A\00", align 1

; Function Attrs: noinline nounwind optnone uwtable
define i64 @my_dog_get_type() #0 {
  %1 = alloca i32, align 4
  %2 = alloca i8*, align 8
  %3 = alloca i64, align 8
  fence seq_cst
  %4 = load volatile i64, i64* @my_dog_get_type.g_define_type_id__volatile, align 8
  %5 = inttoptr i64 %4 to i8*
  store i8* %5, i8** %2, align 8
  %6 = load i8*, i8** %2, align 8
  %7 = icmp ne i8* %6, null
  br i1 %7, label %11, label %8

; <label>:8:                                      ; preds = %0
  %9 = call i32 @g_once_init_enter(i8* bitcast (i64* @my_dog_get_type.g_define_type_id__volatile to i8*))
  %10 = icmp ne i32 %9, 0
  br label %11

; <label>:11:                                     ; preds = %8, %0
  %12 = phi i1 [ false, %0 ], [ %10, %8 ]
  %13 = zext i1 %12 to i32
  store i32 %13, i32* %1, align 4
  %14 = load i32, i32* %1, align 4
  %15 = icmp ne i32 %14, 0
  br i1 %15, label %16, label %20

; <label>:16:                                     ; preds = %11
  %17 = call i8* @g_intern_static_string(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str, i32 0, i32 0))
  %18 = call i64 @g_type_register_static_simple(i64 80, i8* %17, i32 136, void (i8*, i8*)* bitcast (void (i8*)* @my_dog_class_intern_init to void (i8*, i8*)*), i32 32, void (%struct._GTypeInstance*, i8*)* bitcast (void (%struct._MyDog*)* @my_dog_init to void (%struct._GTypeInstance*, i8*)*), i32 0)
  store i64 %18, i64* %3, align 8
  %19 = load i64, i64* %3, align 8
  call void @g_once_init_leave(i8* bitcast (i64* @my_dog_get_type.g_define_type_id__volatile to i8*), i64 %19)
  br label %20

; <label>:20:                                     ; preds = %16, %11
  %21 = load volatile i64, i64* @my_dog_get_type.g_define_type_id__volatile, align 8
  ret i64 %21
}

declare i32 @g_once_init_enter(i8*) #1

declare i64 @g_type_register_static_simple(i64, i8*, i32, void (i8*, i8*)*, i32, void (%struct._GTypeInstance*, i8*)*, i32) #1

declare i8* @g_intern_static_string(i8*) #1

; Function Attrs: noinline nounwind optnone uwtable
define internal void @my_dog_class_intern_init(i8*) #0 {
  %2 = alloca i8*, align 8
  store i8* %0, i8** %2, align 8
  %3 = load i8*, i8** %2, align 8
  %4 = call i8* @g_type_class_peek_parent(i8* %3)
  store i8* %4, i8** @my_dog_parent_class, align 8
  %5 = load i32, i32* @MyDog_private_offset, align 4
  %6 = icmp ne i32 %5, 0
  br i1 %6, label %7, label %9

; <label>:7:                                      ; preds = %1
  %8 = load i8*, i8** %2, align 8
  call void @g_type_class_adjust_private_offset(i8* %8, i32* @MyDog_private_offset)
  br label %9

; <label>:9:                                      ; preds = %7, %1
  %10 = load i8*, i8** %2, align 8
  %11 = bitcast i8* %10 to %struct.MyDogClass*
  call void @my_dog_class_init(%struct.MyDogClass* %11)
  ret void
}

; Function Attrs: noinline nounwind optnone uwtable
define internal void @my_dog_init(%struct._MyDog*) #0 {
  %2 = alloca %struct._MyDog*, align 8
  store %struct._MyDog* %0, %struct._MyDog** %2, align 8
  %3 = load %struct._MyDog*, %struct._MyDog** %2, align 8
  %4 = getelementptr inbounds %struct._MyDog, %struct._MyDog* %3, i32 0, i32 1
  store i32 0, i32* %4, align 8
  call void (i8*, ...) @g_print(i8* getelementptr inbounds ([17 x i8], [17 x i8]* @.str.3, i32 0, i32 0))
  ret void
}

declare void @g_once_init_leave(i8*, i64) #1

; Function Attrs: noinline nounwind optnone uwtable
define void @my_dog_bark(%struct._MyDog*) #0 {
  %2 = alloca %struct._MyDog*, align 8
  store %struct._MyDog* %0, %struct._MyDog** %2, align 8
  call void (i8*, ...) @g_print(i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.1, i32 0, i32 0))
  ret void
}

declare void @g_print(i8*, ...) #1

; Function Attrs: noinline nounwind optnone uwtable
define i32 @main(i32, i8**) #0 {
  %3 = alloca i32, align 4
  %4 = alloca i32, align 4
  %5 = alloca i8**, align 8
  store i32 0, i32* %3, align 4
  store i32 %0, i32* %4, align 4
  store i8** %1, i8*** %5, align 8
  call void @create_dog_normally()
  ret i32 0
}

declare i8* @g_type_class_peek_parent(i8*) #1

declare void @g_type_class_adjust_private_offset(i8*, i32*) #1

; Function Attrs: noinline nounwind optnone uwtable
define internal void @my_dog_class_init(%struct.MyDogClass*) #0 {
  %2 = alloca %struct.MyDogClass*, align 8
  store %struct.MyDogClass* %0, %struct.MyDogClass** %2, align 8
  call void (i8*, ...) @g_print(i8* getelementptr inbounds ([23 x i8], [23 x i8]* @.str.2, i32 0, i32 0))
  ret void
}

; Function Attrs: noinline nounwind optnone uwtable
define internal void @create_dog_normally() #0 {
  %1 = alloca %struct._GObject*, align 8
  %2 = call i64 @my_dog_get_type()
  %3 = call i8* (i64, i8*, ...) @g_object_new(i64 %2, i8* null)
  %4 = bitcast i8* %3 to %struct._GObject*
  store %struct._GObject* %4, %struct._GObject** %1, align 8
  %5 = load %struct._GObject*, %struct._GObject** %1, align 8
  %6 = bitcast %struct._GObject* %5 to %struct._MyDog*
  call void @my_dog_bark(%struct._MyDog* %6)
  %7 = load %struct._GObject*, %struct._GObject** %1, align 8
  %8 = bitcast %struct._GObject* %7 to i8*
  call void @g_object_unref(i8* %8)
  ret void
}

declare i8* @g_object_new(i64, i8*, ...) #1

declare void @g_object_unref(i8*) #1

attributes #0 = { noinline nounwind optnone uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.module.flags = !{!0}
!llvm.ident = !{!1}

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{!"clang version 6.0.0-1ubuntu2 (tags/RELEASE_600/final)"}
