pub mod io {
    use std::{
        fmt::{self, Debug},
        io::{BufRead, BufReader, Stdin},
        str::FromStr,
    };
 
    pub trait IO: fmt::Write {
        fn read_line(&mut self) -> &str;
 
        fn read<F: FromStr>(&mut self) -> F
        where
            F::Err: Debug,
        {
            self.read_line().parse().unwrap()
        }
 
        fn read_iter<'a, T: FromStr>(&'a mut self) -> Iter<'a, T>
        where
            T::Err: Debug,
        {
            Iter {
                iter: self.read_line().split_whitespace(),
                _marker: std::marker::PhantomData,
            }
        }
 
        fn read_array<T: FromStr, const N: usize>(&mut self) -> [T; N]
        where
            T::Err: Debug,
        {
            let mut iter = self.read_iter();
            [(); N].map(|()| iter.next().unwrap())
        }
 
        fn write(&mut self, s: &str);
    }
 
    pub struct Iter<'a, T> {
        iter: std::str::SplitWhitespace<'a>,
        _marker: std::marker::PhantomData<T>,
    }
 
    impl<'a, T: FromStr> Iterator for Iter<'a, T>
    where
        T::Err: Debug,
    {
        type Item = T;
 
        fn next(&mut self) -> Option<Self::Item> {
            let next = self.iter.next()?;
            Some(next.parse().unwrap())
        }
    }
 
    pub struct StdIO {
        reader: BufReader<Stdin>,
        input: String,
        output: String,
    }
 
    impl StdIO {
        pub fn new() -> Self {
            Self {
                reader: BufReader::new(std::io::stdin()),
                input: String::new(),
                output: String::with_capacity(2_000_000),
            }
        }
    }
 
    impl IO for StdIO {
        fn read_line(&mut self) -> &str {
            self.input = String::new();
            self.reader.read_line(&mut self.input).unwrap();
            self.input.trim_end()
        }
 
        fn write(&mut self, s: &str) {
            self.output.push_str(s);
        }
    }
 
    impl fmt::Write for StdIO {
        fn write_str(&mut self, s: &str) -> fmt::Result {
            write!(&mut self.output, "{s}")
        }
    }
 
    impl Drop for StdIO {
        fn drop(&mut self) {
            println!("{}", self.output);
        }
    }
 
    pub struct MockIO<'a> {
        input: std::str::Lines<'a>,
        line: &'a str,
        pub output: String,
    }
 
    impl<'a> MockIO<'a> {
        pub fn new(input: &'a str) -> Self {
            Self {
                input: input.lines(),
                line: "",
                output: String::new(),
            }
        }
 
        pub fn output(&self) -> &str {
            self.output.trim_end()
        }
    }
 
    impl IO for MockIO<'_> {
        fn read_line(&mut self) -> &str {
            self.line = self.input.next().unwrap();
            self.line.trim_end()
        }
 
        fn write(&mut self, s: &str) {
            self.output.push_str(s);
        }
    }
 
    impl fmt::Write for MockIO<'_> {
        fn write_str(&mut self, s: &str) -> fmt::Result {
            write!(&mut self.output, "{s}")
        }
    }
}
