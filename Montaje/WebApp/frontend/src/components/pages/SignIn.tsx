import Form from 'react-bootstrap/Form';
import Button from 'react-bootstrap/Button';
import { useFormik } from 'formik'
import Stack from 'react-bootstrap/Stack';
import { userSchema } from '../../types/user';
import { signIn } from '../../reducers/sign';
import { useDispatch } from 'react-redux';
import { useNavigate } from 'react-router-dom';


const SignInPage = () => {
    const dispatch = useDispatch()
    const navigate = useNavigate()

    const formik = useFormik({
        initialValues: {
            username: "",
            password: ""
        },
        validate: (values) => {
            const res = userSchema.safeParse(values);
            console.log(res.error?.flatten().fieldErrors);
            return res.error?.flatten().fieldErrors;
        },
        onSubmit(values) {
            dispatch(signIn(values))
            navigate("/", { replace: true });
        },
    })

    return (
        <Form onSubmit={formik.handleSubmit}>
            <Stack gap={2}>
                <h1>Sign In</h1>
                <Form.Group>
                    <Form.Label>Username</Form.Label>
                    <Form.Control
                        id='username'
                        name='username'
                        type='text'
                        onChange={formik.handleChange}
                        value={formik.values.username}
                        onBlur={formik.handleBlur}
                    />
                    <Form.Text className='text-danger'>
                        {formik.touched.username && formik.errors.username ? formik.errors.username : ""}
                    </Form.Text>
                </Form.Group>
                <Form.Group>
                    <Form.Label>Password</Form.Label>
                    <Form.Control
                        id='password'
                        name="password"
                        type='password'
                        onChange={formik.handleChange}
                        value={formik.values.password}
                    />
                    <Form.Text className='text-danger'>
                        {formik.touched.password && formik.errors.password ? formik.errors.password : ""}
                    </Form.Text>
                </Form.Group>
                <Button variant='success' type='submit' style={{ alignSelf: "start" }}>Sign In</Button>
            </Stack>
        </Form>
    )
}

export default SignInPage;