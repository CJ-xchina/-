; ModuleID = './code.c'
source_filename = "./code.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-i128:128-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

@str = private unnamed_addr constant [6 x i8] c"hello\00", align 1

; Function Attrs: nounwind optsize uwtable
define dso_local i32 @main() local_unnamed_addr #0 !dbg !17 {
entry:
  tail call void @printHello(ptr null), !dbg !21
  %puts = tail call i32 @puts(ptr nonnull dereferenceable(1) @str), !dbg !21
  ret i32 0, !dbg !22
}

; Function Attrs: nounwind
declare void @printHello(ptr) local_unnamed_addr #1

; Function Attrs: nofree nounwind
declare noundef i32 @puts(ptr nocapture noundef readonly) local_unnamed_addr #2

attributes #0 = { nounwind optsize uwtable "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #1 = { nounwind }
attributes #2 = { nofree nounwind }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!10, !11, !12, !13, !14, !15}
!llvm.ident = !{!16}

!0 = distinct !DICompileUnit(language: DW_LANG_C11, file: !1, producer: "Ubuntu clang version 18.0.0 (++20231105053030+c4798db42edd-1~exp1~20231105173139.829)", isOptimized: true, runtimeVersion: 0, emissionKind: FullDebug, globals: !2, splitDebugInlining: false, nameTableKind: None)
!1 = !DIFile(filename: "code.c", directory: "/home/c/Code/CPP/software-test/\E5\A4\A7\E4\BD\9C\E4\B8\9A2/part1/test/hello", checksumkind: CSK_MD5, checksum: "3ad5c92c53346f19cc1d784e6068d97a")
!2 = !{!3}
!3 = !DIGlobalVariableExpression(var: !4, expr: !DIExpression())
!4 = distinct !DIGlobalVariable(scope: null, file: !5, line: 5, type: !6, isLocal: true, isDefinition: true)
!5 = !DIFile(filename: "./code.c", directory: "/home/c/Code/CPP/software-test/\E5\A4\A7\E4\BD\9C\E4\B8\9A2/part1/test/hello", checksumkind: CSK_MD5, checksum: "3ad5c92c53346f19cc1d784e6068d97a")
!6 = !DICompositeType(tag: DW_TAG_array_type, baseType: !7, size: 56, elements: !8)
!7 = !DIBasicType(name: "char", size: 8, encoding: DW_ATE_signed_char)
!8 = !{!9}
!9 = !DISubrange(count: 7)
!10 = !{i32 7, !"Dwarf Version", i32 5}
!11 = !{i32 2, !"Debug Info Version", i32 3}
!12 = !{i32 1, !"wchar_size", i32 4}
!13 = !{i32 8, !"PIC Level", i32 2}
!14 = !{i32 7, !"PIE Level", i32 2}
!15 = !{i32 7, !"uwtable", i32 2}
!16 = !{!"Ubuntu clang version 18.0.0 (++20231105053030+c4798db42edd-1~exp1~20231105173139.829)"}
!17 = distinct !DISubprogram(name: "main", scope: !5, file: !5, line: 3, type: !18, scopeLine: 4, flags: DIFlagAllCallsDescribed, spFlags: DISPFlagDefinition | DISPFlagOptimized, unit: !0)
!18 = !DISubroutineType(types: !19)
!19 = !{!20}
!20 = !DIBasicType(name: "int", size: 32, encoding: DW_ATE_signed)
!21 = !DILocation(line: 5, column: 5, scope: !17)
!22 = !DILocation(line: 6, column: 5, scope: !17)
