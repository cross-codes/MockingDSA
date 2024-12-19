package commons.annotations;

@java.lang.annotation.Retention(java.lang.annotation.RetentionPolicy.SOURCE)
@java.lang.annotation.Target(java.lang.annotation.ElementType.TYPE)
public @interface MultipleInheritanceDisallowed {
  Class<?> inheritor();
}