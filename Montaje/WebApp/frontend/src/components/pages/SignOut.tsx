import { signOut } from "../../reducers/sign";
import { useEffect } from "react";
import { useDispatch } from "react-redux";
import { useNavigate } from "react-router-dom";
import LoadingSpinner from "../LoadingSpinner";


const SignOut = () => {
    const dispatch = useDispatch();
    const navigate = useNavigate();

    useEffect(() => {
        dispatch(signOut());
        navigate("/", { replace: true });

    }, [dispatch, navigate]);

    return <LoadingSpinner />;
};

export default SignOut;
