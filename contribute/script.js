const togglepassword = document.querySelector("#togglepassword");
const password = document.querySelector("#password");
togglepassword.addEventListener("click",()=>{
    if(password.getAttribute("type") === "password"){
        password.setAttribute("type","text");
        togglepassword.innerHTML = "<i class='fa-solid fa-eye-slash'></i>";
    }else{
        password.setAttribute("type","password");
        togglepassword.innerHTML = "<i class='fa-solid fa-eye'></i>";
    }
})